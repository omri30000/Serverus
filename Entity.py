class Entity():
    def __init__(self,ip,mac):
        self._ip_add = ip
        self._mac_add = mac

    def get_ip_add(self):
        return self._ip_add
    
    def get_mac_add(self):
        return self._mac_add