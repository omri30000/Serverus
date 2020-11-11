#!/usr/bin/env python3

# This is the sniffer file, it will parse the data from the sniffs to a data for the model

from scapy.all import *
import socket
import os

import time
from datetime import datetime

from Packet import *

import csv
import threading

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
            
            self.lock.acquire()

            self.csvfile = open('sniffs.csv', 'w', newline='')
            fieldnames = ['source_mac', 'source_IP', 'dest_IP', 'source_port', 
            'dest_port', 'protocol', 'length', 'data', 'arrival_time']
            self.csv_writer = csv.DictWriter(self.csvfile, fieldnames=fieldnames)
            self.csv_writer.writeheader()

            self.lock.release()

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
        self.csvfile.close()
        

    def start_sniffing(self):
        """
        The function allow the user to start the sniffer work
        :param self: the instance of Sniffer
        :type self: sniffer
	    :return: no return value
	    :rtype: None
	    """
        sniff(prn=self.__write_packet, count=20)
    

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
            self.lock.acquire()
            pack = Packet(datetime.now(), pkt)
            self.csv_writer.writerow(pack.asdict())
        except Exception as e:
            print(e)
        finally:
            self.lock.release()


def main():
    mySniffer = Sniffer()

    mySniffer.start_sniffing()


if __name__ == "__main__":
    main()