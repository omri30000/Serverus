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

        self.db_manager = DatabaseManager.DatabaseManager("/home/ofir/database.sqlite")
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

    def add_product(self):
        pass

    def __manage_conversation(self, sock):
        EVENT_SIZE_BYTES = 9

        product_message = bytearray(sock.recv(1024))
        events = []
        computer_id = int(product_message[0])
        for i in range(1, len(product_message), EVENT_SIZE_BYTES):
            event = Event.Event.create_from_msg(product_message[i: i + EVENT_SIZE_BYTES])
            
            self.db_manager_lock.acquire()
            self.db_manager.insert_event(event, computer_id)
            self.db_manager_lock.release()

        # save to sql - events

        try:
            last_date = db_manager.get_last_date(computer_id)
        except Exception as e:
            last_date = None

        # read from sql
        
        self.db_manager_lock.acquire()
        outer_events = self.db_manager.get_dangerous_events(computer_id, last_date)
        self.db_manager_lock.release()
        
        msg = bytearray([0])

        for eve in outer_events:
            msg += eve.to_packet()
        
        sock.sendall(msg)

        self.db_manager.set_last_date(computer_id)

        time.sleep(2)
        sock.close()


    def __make_config_file(self, product_id):
        """
        The function will create a string that can be added to a json file.
        """
        data = {"ProductID": product_id,
        "ServerDomain": SERVER_DOMAIN,
        "ServerPort": LISTENING_PORT,
        "DefenderListenPort": 4123}

        with open('Configuration.json', 'w') as json_file:
            json.dump(data, json_file)




def main():
    my_server = Server(LISTENING_PORT)
    my_server.serve()


if __name__ == '__main__':
    main()

