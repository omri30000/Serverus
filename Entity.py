# This is the Event class

class Event():

    def __init__(self,ip,mac):
        """Constructor

        Args:
            ip ({str}): The entity's ip address
            mac ({str}): The entity's MAC address
        """        
        self.ip_add = ip
        self

    """getters functions"""
    def get_ip_add(self):
        return self.ip_add
    
    def get_mac_add(self):
        return self.mac_add
