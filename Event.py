# This is the Event class
from datetime import datetime 
class Event:
    def __init__(self,msg):
        print(msg)
        self.level = msg[0]
        self.ip_add =".".join([str(i) for i in msg[1:5]])
        self.date = datetime.now()
        print(self.level,self.ip_add)
    """
    def __init__(self,ip,level,date):
        Constructor

        Args:
            ip ({str}): The entity's ip address
             
        self.ip_add = ip
        self.level = level
        self.date = date
    """

    """getters functions"""
    def get_ip_add(self):
        return self.ip_add
    
    def get_level(self):
        return self.level
    
    def get_date(self):
        return self.date
    
    
    def calc_date(self):
        """
        This function returns the amount of milliseconds that passed since the start of day until the event's date

        Returns:
            int: hour in milliseconds
        """
        return self.date.hour * 60*60 *1000 + self.date.minute* 60 *1000 + self.date.second * 1000 +int(self.date.microsecond /1000)
    

    def to_packet(self):
        """
        This function builds the binary message of this event for the packet to the global server
        Returns:
            byteAarray: the binary message
        """
        mes = bytearray()  # create empty bytearray
        
        mes.append(self.level)  # add the level of blocking
        
        for i in self.ip_add.split('.'): # add IP address
            mes.append(int(i))

        date = str(self.calc_date())  # add date (number by number)
        for digit in date:
            mes.append(int(digit))

        # example of a message (level-4/IP-127.0.0.1/time-3600000):
        # bytearray(b'\x04\x7f\x00\x00\x01\x03\x06\x00\x00\x00\x00\x00')
        return mes

