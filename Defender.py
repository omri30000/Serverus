import os
from crontab import CronTab
import datetime

import Rule
import Entity
# This is the Defender class, which will execute the defensive actions against hostile entities.

class Defender():
    #TODO : add single-tone feature
    def __init__(self):
        pass
    
    """
    Primary function, provides the defence from hostile entity, according to the anomaly level
    Input:
    entity - the hostile entity
    level - the anomaly level {1-4}
    """
    def defend(self,entity,level):
        self.__close_socket(entity)

        if level == 1:
            return

        rule = Rule.Rule(entity,level)
        self.__block(rule)

        if level == 4:
            self.__inform(entity)


    """
    This function cancel entity blocking
    Input:
        entity: Entity the cancel the block for
    Output:
        None
    """
    def cancel_action(self, entity):
        ERROR_CODE = "256"
        msg = ""
        while str(msg).find(ERROR_CODE) < 0: 
            msg = os.system("iptables -D INPUT %s -j DROP"%(Rule.Rule(entity,3).write_rule()))
    """
    This function closes a specific socket.
    input:
        entity:The entity at the end of the socket 
    Output:
        none
    """
    def __close_socket(self, entity):
        #terminates all sockets with entity
        os.system("ss --kill -nt dst %s "%(entity.ip_add))

    """ 
    This function blocks an entity at the fire-wall
    Input: 
        entity: The entity to block
    Output:
    None
    """
    def __block(self, rule):
        if rule.is_temp():
            cron = CronTab(user='root')
            time_to_delete = rule.get_date() + datetime.timedelta(minutes=2) #time to disable blocking
            rule_to_write = "sudo iptables -D INPUT %s -j DROP"%(rule.write_rule())

            job = cron.new(command = (rule_to_write + "| grep -v  " +rule_to_write + "| crontab -"))
            job.setall("%d %d * * *"%(time_to_delete.minute,time_to_delete.hour))
            cron.write()


        os.system("iptables -A INPUT %s -j DROP"%(rule.write_rule()))

    #level 4 (not in this sprint)
    def __inform(self, rule):
        pass