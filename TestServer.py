#!/usr/bin/env python3

import Server
import DatabaseManager
import Defender
import Config
import socket

def main():
    HOST = '127.0.0.1'  # The defender's IP address
    PORT = 5556        # The port used by the defender

    a = bytearray(b'\x01\x08\x08\x01\x01\x00\x00\x00\xff')

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(a)

    print('Sent')


if __name__ == '__main__':
    main()