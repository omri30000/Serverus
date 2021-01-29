#!/usr/bin/env python3

import Server
import DatabaseManager
import Defender
import Config
import socket

HOST = '127.0.0.1'  # The defender's IP address
PORT = 9876  # The port used by the defender


def main():

    a = bytearray(b'\x04\x09\x0B\x04\x01\x00\x36\xfe\x80')

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(a)

    print('Sent')


if __name__ == '__main__':
    main()
