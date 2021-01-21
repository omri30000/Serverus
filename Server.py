import socket
import threading
import time
import DatabaseManager


class Server:
    def __init__(self, listening_port):
        self.LISTEN_PORT = listening_port

        # Create a TCP/IP socket
        self.listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connecting to remote computer
        server_address = ('', self.LISTEN_PORT)
        self.listening_sock.bind(server_address)

        self.threads = []

        self.db_manager = DatabaseManager.DatabaseManager("general_db.sqlite")
        
        
    def serve(self):
        self.listening_sock.listen(1)  # wait for connection with product
        
        while True:
            # Create a new conversation socket
            product_soc, product_address = self.listening_sock.accept()

            try:
                t = threading.Thread(target = self.__manage_conversation, args = product_soc)
                t.start()
                self.threads.append(t)

            except ConnectionResetError as e:
                print(e)
                print("An existing connection was forcibly closed by the remote host")
            
        for thread in self.threads:
            thread.join()

        self.listening_sock.close()


    def __manage_conversation(self, sock):
        product_message = bytearray(sock.recv(1024))

        #todo: add parsing to the message



def main():
    pass


if __name__ == '__main__':
    main()

