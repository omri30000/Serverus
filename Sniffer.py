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


packets_queue = queue.Queue()

def main():
    threading.Thread(target=handle_packets_queue, daemon=True).start()
    sniff(prn=parse_packet)
    

def handle_packets_queue():
    global packets_queue
    while True:
        if not packets_queue.empty()
            pack = packets_queue.get()
            # todo: add to csv file
            packets_queue.task_done()

def parse_packet(pkt):
    global packets_queue

    # get the packet arrival time
    time = datetime.datetime.now()

    try:
        packets_queue.put(Packet(time, pkt))
    except:
        print("An error occoured while parsing packet")
    


if __name__ == '__main__':
    main()