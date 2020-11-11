#!/usr/bin/env python3

# This is the sniffer file, it will parse the data from the sniffs to a data for the model

from scapy.all import *
import socket
import os

import datetime
import time

from Packet import *

import csv
import queue
import threading

class Sniffer:
    def __init__(self):
        self._packets_queue = queue.Queue()


    def start_sniffing(self):
        threading.Thread(target=self.__handle_packets_queue, daemon=True).start()
        sniff(prn=self.__parse_packet, count=20)
    

    def __handle_packets_queue(self):
        with open('sniffs.csv', 'a', newline='') as csvfile:
            fieldnames = ['source_mac', 'source_IP', 'dest_IP', 'source_port', 
            'dest_port', 'protocol', 'length', 'data', 'arrival_time']
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            writer.writeheader()

            while True:
                if not self._packets_queue.empty():
                    pack = self._packets_queue.get()
                    
                    writer.writerow(pack.asdict())
                    
                    self._packets_queue.task_done()

    def __parse_packet(self, pkt):
        # print('hello')
        # get the packet arrival time

        # todo: fix time issues and send it to Packet
        # time = datetime.datetime.now()

        try:
            self._packets_queue.put(Packet(15, pkt))
        except Exception as e:
            print(e)

        self._packets_queue.join()


def main():
    mySniffer = Sniffer()

    mySniffer.start_sniffing()


if __name__ == "__main__":
    main()