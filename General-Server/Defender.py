import os
from crontab import CronTab
import datetime
import socket
import time
import threading

from datetime import datetime, timedelta

import Rule
import Event
import Log
import Config

COMPUTER_ID = 1
LISTEN_PORT = 4123


class Defender:
    """
    This is the Defender class, which will execute the defensive actions against hostile entities.
    """
    count = 0  # amount of objects created

    def __init__(self):
        """Constructor

        Raises:
            Exception: If a Defender object was already created
        """

        if Defender.count > 0:
            raise Exception("Cant create more than one Defender (Singleton Class)")

        self.events = []
        self.thread = threading.Thread(target=self.__inform)
        self.cron = CronTab(user='root')
        self.emerge = False  # level 4 has been found
        
        try:
            # self.log = Log.Log(input("Enter log file name: "))
            self.log = Log.Log("Loglog.txt")
        except Exception as e:
            raise e

        self.thread.start()

    def defend(self, event, local = False):
        """
        Primary function, provides the defence from hostile event, according to the anomaly level.
        Args:
            event ({event}): The hostile event the defend from
        """
        print(type(event))
        print("cululululu")

        if not local:
            self.events += [event]

        self.__close_socket(event)

        if event.get_level() == 1:
            return

        rule = Rule.Rule(event)

        # for upgrading

        self.__block(rule)

        if event.get_level() == 4 and not local:
            self.emerge = True

    def cancel_action(self, event):
        """This function cancel fire-wall blocking

        Args:
            event ({Event}): which event to cancel the block for
        """
        ERROR_CODE = "256"
        msg = ""
        while str(msg).find(ERROR_CODE) < 0:
            msg = os.system("iptables -D INPUT %s -j DROP" % (Rule.Rule(event, 3).write_rule()))
        self.log.add_unblock_record(event)

    def __close_socket(self, event):
        """The function closes a specific socket

        Args:
            event ({Event}): Hostile event
        """
        # terminates all sockets with event
        os.system("ss --kill -nt dst %s " % (event.get_ip_add()))
        # os.system("tcpkill ip host %s"%(event.get_ip_add()))
        self.log.add_block_record(event, 1)

    def __block(self, rule):

        """This function blocks an event at the firewall

        Args:
            rule ({Rule}): The rule to write in the firewall
        """

        RULE_NOT_FOUND = 256
        # check if rule already exists
        try:
            if int(os.system("iptables -C INPUT %s -j DROP" % (rule.write_rule()))) != RULE_NOT_FOUND:
                # rule already exists
                if not rule.is_temp():
                    self.__delete_cron(rule.write_rule())
                return

        except Exception as e:
            self.log.add_error_record(e)

        if rule.is_temp():
            time_to_delete = rule.get_date() + timedelta(minutes=2)  # time to disable blocking
            # print("hello")
            rule_to_write = "/sbin/iptables -D INPUT %s -j DROP"%(rule.write_rule())

            job = self.cron.new(command=rule_to_write + "; sudo crontab -l | grep \"" + rule_to_write + "\" | crontab -r")
            job.setall("%d %d * * *" % (time_to_delete.minute, time_to_delete.hour))
            self.cron.write(user='root')

            # self.log.add_block_record(event, 2)
        # else:
        #   self.log.add_block_record(event, 3)

        os.system("/sbin/iptables -A INPUT %s -j DROP" % (rule.write_rule()))

    def __delete_cron(self, data):
        """
        This function deletes a cron from the crontab lists

        Args:
            data ({str}): The cron action - the data of the cron
        """
        for job in self.cron:
            # print(job.command)
            if data in job.command:
                self.cron.remove(job)
        self.cron.write()

    def __inform(self):
        """[summary]

        Args:
        """

        while True:
            start = datetime.now()
            while not self.emerge and (datetime.now() - start).seconds <= 10*60:
                time.sleep(10)  # sleep 10 seconds
            
            self.emerge = False

            message = bytearray([COMPUTER_ID])
            for i in self.events:
                message += i.to_packet()
            # requires lock
            self.events = []
            
            # get all events to send
            data = bytearray()
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((Config.SERVER_IP, Config.SERVER_PORT))
                # print("message: ", message)
                s.sendall(message)
                data = s.recv(1024)

            if len(data) < 2:  # there are no events
                msg_code = int(data[0])
                # block events from global server
                for i in range(1, len(data), 9):
                    self.defend(Event.Event.create_from_msg(bytearray(data[i:i+9])), local=True)  # at level 3


def main():    
    defender = Defender()
    listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    listening_sock.bind(('', LISTEN_PORT))
    listening_sock.listen(1)  # wait for connection with the model

    while True:
        try:
            # Create a new conversation socket
            model_soc, model_address = listening_sock.accept()
            
            msg_answer = model_soc.recv(1024)
            defender.defend(Event.Event.create_from_msg(bytearray(msg_answer)))
        except Exception:
            listening_sock.close()

    
if __name__ == '__main__':
    main()
