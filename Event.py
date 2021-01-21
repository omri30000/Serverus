# This is the Event class
from datetime import datetime 
class Event:
    def __init__(self,msg):
        print(msg)
        self.level = msg[0]
        self.ip_add =".".join([str(i) for i in msg[1:5]])
        date = sum([pow(256,i)  * int(msg[5+i]) for i in range(4)])
        today = datetime.date.today()
        if calc_date_param(datetime.now() > date):
            today -= timedelta(days=1)
        self.date = today. + timedelta(milliseconds = date)    
        print(self.date.days,self.date.hour,self.date.minute,self.date.second)
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
    
    
    def calc_date_param(time):
        return time.hour * 60*60 *1000 + time.minute* 60 *1000 + time.second * 1000 +int(time.microsecond /1000)

    def calc_date(self):
        """
        This function returns the amount of milliseconds that passed since the start of day until the event's date

        Returns:
            int: hour in milliseconds
        """
        return calc_date_param(self.date)
    

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
        
        BASE = 256
        date = self.calc_date()
        vals =[]
        while date >0:
            vals += [date%BASE]
            date //= BASE
        
        if len(vals) < 4:
            vals += [0]*(4-len(vals))

        mes.append(vals[::-1])
        return mes

