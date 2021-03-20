#!/usr/bin/env python3

# This is the sniffer file, it will parse the data from the sniffs to a data for the model

from scapy.all import *
import socket
import os
import sys

import time
from datetime import datetime

from Packet import *

import threading
import zmq
PIPE = "/tmp/fifo-pipe1"
class Sniffer:
    amount = 0

    def __init__(self):
        """
        The initializer of the Sniffer object. allow the user to create a Sniffer and initial it. 
        :param self: the instance of Sniffer
        :type self: sniffer
	    :return: no return value
	    :rtype: None
	    """
        if Sniffer.amount == 0:
            Sniffer.amount += 1
            
            self.lock = threading.Lock()
            self.a = 0
            self.lock.acquire()
            try:
                self.context = zmq.Context()
                self.socket = self.context.socket(zmq.PUSH)
                self.socket.connect("ipc://%s" % PIPE)
            except Exception as e:
                print(e)

            self.lock.release()
            self.packet_index = 0

        else:
            raise Exception("can't create more than one sniffer!")


    def __del__(self):
        """
        The destructor of the Sniffer object
        :param self: the instance of Sniffer
        :type self: sniffer
	    :return: no return value
	    :rtype: None
	    """
        Sniffer.amount -= 1
        

    def start_sniffing(self):
        """
        The function allow the user to start the sniffer work
        :param self: the instance of Sniffer
        :type self: sniffer
	    :return: no return value
	    :rtype: None
	    """
        sniff(prn=self.__write_packet)


    def start_reading(self, file_path):
        """
        The function allow the user to start the sniffer work
        :param self: the instance of Sniffer
        :type self: sniffer
	    :return: no return value
	    :rtype: None
	    """
        sniff(offline=file_path, prn=self.__write_packet, store=0)


    def __write_packet(self, pkt):
        """
        The callback function will write a single packet to the csv file
        :param self: the instance of Sniffer
        :type self: sniffer
        :param pkt: the packet that will be written to the file
        :type pkt: scapy.packet
	    :return: no return value
	    :rtype: None
	    """
        try:
            pack = Packet(pkt)
            
            self.socket.send(pack.cast_to_json().encode())
            self.a +=1
            print(self.a)
        except Exception as e:
            print(e)


def main():
    my_sniffer = Sniffer()
    if len(sys.argv) == 1:
        print("sniffing")
        my_sniffer.start_sniffing()
    else:
        file_path = sys.argv[1]  # index 1 is the pcap file path
        my_sniffer.start_reading(file_path)


if __name__ == "__main__":
    main()
