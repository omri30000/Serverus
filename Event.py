# This is the Event class

class Event():

    def __init(self,msg):
        self.level = msg[0]
        self.ip =".".join([str(i) for i in msg_answer[1:5]])
        self.date = msg_answer[6]

    def __init__(self,ip,level,date):
        """Constructor

        Args:
            ip ({str}): The entity's ip address
        """        
        self.ip_add = ip
        self.level = level
        self.date = date


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
        return self.date.hour * 60*60 *1000 + self.date.minute* 60 *1000 + self.date.second * 1000 + self.date.microseconds /1000;
    

    def to_packet(self):
        """This function builds the binary message of this event for the packet to the global server

        Returns:
            byteAarray: the binary message
        """
        mes = bytearray()
        mes.append(self.level)
        for i in ip.split('.'):
            mes.append(int(i))
        #mes.append(self.calc_date())
        mes.append(self.date)
        return mes

