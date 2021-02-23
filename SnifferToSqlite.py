#!/usr/bin/env python3

# This is the sniffer file, it will parse the data from the sniffs to a data for the model

from scapy.all import *
import socket
import os

import time
from datetime import datetime

from Packet import *

import csv
import sqlite3
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
            self.a = 0
            self.lock.acquire()
            
            self.db = sqlite3.connect('../db_file.sqlite',isolation_level = None)

            self.db_cursor = self.db.cursor()
            self.db_cursor.execute('pragma journal_mode=wal;')
            #self.db_cursor.execute('PRAGMA journal_size_limit=10;')

            print("ok")
            # Create packets table

            try:
                self.db_cursor.execute('''CREATE TABLE packets
                        (id INTEGER PRIMARY KEY AUTOINCREMENT, source_mac text, source_IP text, dest_IP text, source_port real, 
                        dest_port real, protocol text, length real, data text, arrival_time text)''')
            except Exception:
                pass

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
        self.db.commit()
        self.db.close()
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
            print("go")
            self.db_cursor.execute(pack.cast_to_sql_statement())
            
            self.db_cursor.execute("PRAGMA wal_checkpoint(FULL);")
            self.a += 1
            print("written to DB " + str(self.a))

        except Exception as e:
            #rint(e)
            pass
        finally:
            self.lock.release()


def main():
    mySniffer = Sniffer()

    mySniffer.start_sniffing()


if __name__ == "__main__":
    main()
