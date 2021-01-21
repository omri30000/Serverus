import socket
import time


class Server:
    def __init__(self, listening_port):
        self.LISTEN_PORT = listening_port

        # Create a TCP/IP socket
        self.listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connecting to remote computer
        server_address = ('', self.LISTEN_PORT)
        self.listening_sock.bind(server_address)
        
        
    def serve(self):
        self.listening_sock.listen(1)  # wait for connection with client
        
        # Create a new conversation socket
        client_soc, client_address = self.listening_sock.accept()

        while True:
            client_message = client_soc.recv(1024)

        
        self.listening_sock.close()



def main():
    pass




if __name__ == '__main__':
    main()

