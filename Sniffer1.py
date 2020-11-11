#!/usr/bin/env python3

# This is the sniffer file, it will parse the data from the sniffs to a data for the model

from scapy.all import *
import socket
import os

import time
from datetime import datetime

from Packet import *

import csv
import queue
import threading

class Sniffer:
    amount = 0
    def __init__(self):
        if Sniffer.amount == 0:
            Sniffer.amount += 1
            self._packets_queue = queue.Queue()

        else:
            raise Exception("can't create more than one sniffer!")


    def start_sniffing(self):
        threading.Thread(target=self.__handle_packets_queue, daemon=True).start()
        sniff(prn=self.__parse_packet, count=20)

        self._packets_queue.join()
    

    def __handle_packets_queue(self):
        with open('sniffs1.csv', 'a', newline='') as csvfile:
            fieldnames = ['source_mac', 'source_IP', 'dest_IP', 'source_port', 
            'dest_port', 'protocol', 'length', 'data', 'arrival_time']
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            writer.writeheader()

            while True:
                if not self._packets_queue.empty():
                    pack = self._packets_queue.get()
                    
                    writer.writerow(pack.asdict())
                    print(1)
                    
                    self._packets_queue.task_done()

    def __parse_packet(self, pkt):
        t = datetime.now()

        try:
            self._packets_queue.put(Packet(t, pkt))
        except Exception as e:
            print(e)

        # self._packets_queue.join()


def main():
    mySniffer = Sniffer()

    mySniffer.start_sniffing()


if __name__ == "__main__":
    main()