# This is the Event class

class Event():

    def __init__(self,ip,level,date):
        """Constructor

        Args:
            ip ({str}): The entity's ip address
        """        
        self.ip_add = ip
        self.level = level
        self.date = date
       # self.date = calc_date()


    """getters functions"""
    def get_ip_add(self):
        return self.ip_add
    
    def get_level(self):
        return self.level
    
    def get_date(self):
        return self.date
    
    def to_packet(self):
        
