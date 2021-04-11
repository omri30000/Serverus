import socket
import threading
import time
import DatabaseManager
import Event
import datetime

SERVER_DOMAIN = "defence.rocks"
LISTENING_PORT = 443

class Server:
    def __init__(self, listening_port):
        #self.products = {}
        self.products_lock = threading.Lock()

        self.LISTEN_PORT = listening_port

        # Create a TCP/IP socket
        self.listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connecting to remote computer
        server_address = ('', self.LISTEN_PORT)
        self.listening_sock.bind(server_address)

        self.threads = []

        self.db_manager = DatabaseManager.DatabaseManager("/home/magshimim/idps-20-21/database.sqlite")
        self.db_manager_lock = threading.Lock()

    def serve(self):
        self.listening_sock.listen(1)  # wait for connection with product
        
        while True:
            # Create a new conversation socket
            product_soc, product_address = self.listening_sock.accept()

            try:
                t = threading.Thread(target=self.__manage_conversation, args=(product_soc,))
                t.start()
                self.threads.append(t)

            except ConnectionResetError as e:
                print(e)
                print("An existing connection was forcibly closed by the remote host")
            
        for thread in self.threads:
            thread.join()

        self.listening_sock.close()

    def __manage_conversation(self, sock):
        EVENT_SIZE_BYTES = 9

        product_message = bytearray(sock.recv(1024))
        events = []
        computer_id = int(product_message[0])
        print(computer_id)
        for i in range(1, len(product_message), EVENT_SIZE_BYTES):
            event = Event.Event.create_from_msg(product_message[i: i + EVENT_SIZE_BYTES])
            
            self.db_manager_lock.acquire()
            self.db_manager.insert_event(event, computer_id)
            self.db_manager_lock.release()

        # save to sql - events

        self.db_manager_lock.acquire()
        last_date = self.db_manager.get_last_date(computer_id)
        self.db_manager_lock.release()

        # read from sql
        self.db_manager_lock.acquire()
        outer_events = self.db_manager.get_dangerous_events(computer_id, last_date)
        outer_events += self.db_manager.get_rules_by_level_and_time(computer_id, last_date,5)
        outer_events += self.db_manager.get_deleted_rules(computer_id)

        self.db_manager_lock.release()

        
        msg = bytearray([computer_id])

        for eve in outer_events:
            msg += eve.to_packet()
        sock.sendall(msg)

        self.db_manager_lock.acquire()
        self.db_manager.set_last_date(computer_id)
        self.db_manager_lock.release()

        #time.sleep(2)
        sock.close()


    def __make_config_file(self, product_id):
        """
        The function will create a string that can be added to a json file.
        """
        data = {
                "General" : {
                    "ProductID": product_id,
                },   
                "Model" :
                {
                    "FM_Limit": 5000,
                    "M": 7,
                    "AD_Limit":50000,
                    "Learning_Rate": 0.01,
                    "Hidden_Layer_Ratio": 0.75
                },
            "Communication" :
            {
                "ServerDomain": SERVER_DOMAIN,
                "ServerPort": LISTENING_PORT,
                "DefenderListenPort": 4123
            }
        }
        
        with open('Configuration.json', 'w') as json_file:
            json.dump(data, json_file)




def main():
    my_server = Server(LISTENING_PORT)
    my_server.serve()


if __name__ == '__main__':
    main()

