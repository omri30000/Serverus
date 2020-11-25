class Entity():
    
    def __init__(self,ip,mac):
        """Constructor

        Args:
            ip ({str}): The entity's ip address
            mac ({str}): The entity's MAC address
        """        
        self._ip_add = ip
        self._mac_add = mac


    """getters functions"""
    def get_ip_add(self):
        return self._ip_add
    
    def get_mac_add(self):
        return self._mac_add