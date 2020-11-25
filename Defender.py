import os
from crontab import CronTab
import datetime

import Rule
import Entity

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
        pass
    
    
    def defend(self,entity,level):
        """ 
        Primary function, provides the defence from hostile entity, according to the anomaly level.
        Args:
            entity ({Entity}): The hostile entity to block
            level ({int}): The Blocking level {1...4}
        """       
        self.__close_socket(entity)

        if level == 1:
            return

        rule = Rule.Rule(entity,level == 2)
        self.__block(rule)

        if level == 4:
            self.__inform(entity)


    def cancel_action(self, entity):
        """This function cancel fire-wall blocking

        Args:
            entity ({Entity}): which Entity to cancel the block for
        """        
        ERROR_CODE = "256"
        msg = ""
        while str(msg).find(ERROR_CODE) < 0: 
            msg = os.system("iptables -D INPUT %s -j DROP"%(Rule.Rule(entity,3).write_rule()))
    

    def __close_socket(self, entity):
        """The function closes a specific socket

        Args:
            entity ({Entity}): Entity to block
        """        
        #terminates all sockets with entity
        os.system("ss --kill -nt dst %s "%(entity.get_ip_add()))


    def __block(self, rule):
        """This function blocks an entity at the firewall

        Args:
            rule ({Rule}): The rule to write in the firewall 
        """        
        if rule.is_temp():
            cron = CronTab(user='root')
            time_to_delete = rule.get_date() + datetime.timedelta(minutes=1) #time to disable blocking
            rule_to_write = "/sbin/iptables -D INPUT %s -j DROP"%(rule.write_rule())

            job = cron.new(command = rule_to_write +"; crontab -l | grep \"" +rule_to_write + "\" | crontab -r")
            job.setall("%d %d * * *"%(time_to_delete.minute,time_to_delete.hour))
            cron.write()


        os.system("/sbin/iptables -A INPUT %s -j DROP"%(rule.write_rule()))

    #level 4 (not in this sprint)
    def __inform(self, rule):
        """[summary]

        Args:
            rule ([type]): [description]
        """        
        pass