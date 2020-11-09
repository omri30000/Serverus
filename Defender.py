import os
from enum import enum

import Rule


class Defender():
    
    def __init__(self):
        pass
    
    def defend(self,entity,level):
        self.__close_socket(entity)

        if(level == 1):
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
    def __cancelAction(self, entity):
        os.system("iptables")

    """
    This function closes a specific socket.
    input:
        entity:The entity at the end of the socket 
    Output:
        none
    """
    def __close_socket(self, enetity):
        #check if the socket exists -- try and catch
        os.system("ss --kill -nt dst {}{}"%(entity.ip,entity.port))

    """
    This function blocks an entity at the fire-wall
    Input: 
        entity: The entity to block
    Output:
    None
    """
    def ___block(self, rule):
        if rule.is_temp:
            #create crontab 
            pass

        os.system("iptables -A INPUT {} -j ACCEPT"%(rule.write_rules()))


    def __inform(self, rule):
        pass