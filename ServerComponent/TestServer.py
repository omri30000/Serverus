#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # The defender's IP address
PORT = 4123  # The port used by the defender


def main():

    a = bytearray(b'\x04\x09\x0B\x04\x01\x00\x36\xfe\x80')
    
    b = bytearray(9)
    
    b[0] = 4
    b[1] = 9
    b[2] = 11
    b[3] = 4
    b[4] = 1
    b[5] = 0
    b[6] = 0
    b[7] = 3
    b[8] = 232
    

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(b)

    print('Sent')


if __name__ == '__main__':
    main()
