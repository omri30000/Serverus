
import os
from crontab import CronTab
import datetime
import socket
import time
import threading

from datetime import datetime

import Rule
import Entity
import Log

# This is the Defender class, which will execute the defensive actions against hostile entities.

class Defender():

    count = 0 #amount of objects created

    def __init__(self):
        """Constructor

        Raises:
            Exception: If a Defender object was already created
        """

        if Defender.count > 0:
            raise Exception("Cant create more than one Defender (Singletone Class)")

        self.thread = threading.Thread(target=inform,args=(self))
        self.cron = CronTab(user="root")
        self.emerge = False #level 4 has been found
        try:
            self.log = Log.Log(input("Enter log file name: "))
        except Exception as e:
            raise e
        thread.start()


    def defend(self,entity,level):
        """
        Primary function, provides the defence from hostile entity, according to the anomaly level.
        Args:
            entity ({Entity}): The hostile entity to block
            level ({int}): The Blocking level {1...4}
        """
        self.__close_socket(self, entity)

        if level == 1:
            return

        rule = Rule.Rule(entity,level == 2)

        #for upgrading

        self.__block(entity, rule)

        if level == 4:
            self.emerge = 
    def cancel_action(self, entity):
        """This function cancel fire-wall blocking

        Args:
            entity ({Entity}): which Entity to cancel the block for
        """
        ERROR_CODE = "256"
        msg = ""
        while str(msg).find(ERROR_CODE) < 0:
            msg = os.system("iptables -D INPUT %s -j DROP"%(Rule.Rule(entity,3).write_rule()))
        self.log.add_unblock_record(entity)



    def __close_socket(self, entity):
        """The function closes a specific socket

        Args:
            entity ({Entity}): Entity to block
        """
        #terminates all sockets with entity
        os.system("ss --kill -nt dst %s "%(entity.get_ip_add()))
        self.log.add_block_record(entity,1)

    def


    def __block(self, entity, rule):

        """This function blocks an entity at the firewall

        Args:
            rule ({Rule}): The rule to write in the firewall
        """


        RULE_NOT_FOUND = 256
        #check if rule already exists
        try:
            if int(os.system("iptables -C INPUT %s -j DROP"%(rule.write_rule()))) != RULE_NOT_FOUND:
                #rule already exists
                if not rule.is_temp():
                    self.__delete_cron(rule.write_rule())
                return

        except Exception as e:
            self.log.add_error_record(e)


        if rule.is_temp():
            time_to_delete = rule.get_date() + datetime.timedelta(minutes=2) #time to disable blocking
            rule_to_write = "/sbin/iptables -D INPUT %s -j DROP"%(rule.write_rule())

            job = self.cron.new(command = rule_to_write +"; crontab -l | grep \"" +rule_to_write + "\" | crontab -r")
            job.setall("%d %d * * *"%(time_to_delete.minute,time_to_delete.hour))
            self.cron.write()
            self.log.add_block_record(entity, 2)
        else:
            self.log.add_block_record(entity, 3)


        os.system("/sbin/iptables -A INPUT %s -j DROP"%(rule.write_rule()))


    def __delete_cron(self,data):
        """
        This function deletes a cron from the crontab lists

        Args:
            data ({str}): The cron action - the data of the cron
        """
        for job in self.cron:
            print(job.command)
            if data in job.command:
                self.cron.remove(job)
        self.cron.write()


    def __inform(self):
        """[summary]

        Args:
        """

        while True:
            start = datetime.now().time()
            while not found and  (datetime.now().time() - start).minutes <= 10:
                time.sleep(10) #sleep 10 seconds

            
            #get all events to send
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((HOST, PORT))
                s.sendall(message)
                data = s.recv(1024)
            #parseData
            for i in rules:
                self.defend(entity,rule) #at level3

        pass

def main():
    defend = Defender()


if __name__ == '__main__':
    main()