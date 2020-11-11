import os
from crontab import CronTab
import datetime

import Rule


class Defender():
    #TODO : add single-tone feature
    def __init__(self):
        pass
    
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
        msg  = ""
        while "256" not in msg: 
            msg = os.system("iptables -D input {} -j DROP"%(Rule.Rule(entity,3).write_rule()))

    """
    This function closes a specific socket.
    input:
        entity:The entity at the end of the socket 
    Output:
        none
    """
    def __close_socket(self, entity):
        os.system("ss --kill -nt dst %s %d"%(entity.get_ip(),entity.get_port()))

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
            time_to_delete = rule.get_date() + datetime.timedelta(hours=2) #time to disable blocking
            rule = "iptables -D input {} -j DROP"%(rule.write_rule)

            job = cron.new(command = rule + "| grep -v  " +rule + "| crontab -" )
            job.setall("%d %d * * *"%(time_to_delete.minutes,time_to_delete.hours))
            cron.write()


        os.system("iptables -A INPUT {} -j DROP"%(rule.write_rules()))

    #level 3 (not in this sprint)
    def __inform(self, rule):
        pass