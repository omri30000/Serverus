#!/usr/bin/env python3

# This is the sniffer file, it will parse the data from the sniffs to a data for the model

from scapy.all import *
import socket
import datetime
import os
#  from geoip import geolite2
import time

def main():
    sniff(prn=parse_packet)


def parse_packet(pkt):
    # get the packet arrival time
    time = datetime.datetime.now()
    pkt.show()



if __name__ == '__main__':
    main()