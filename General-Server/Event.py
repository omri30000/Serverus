# This is the Event class
import datetime


class Event:
    
    def __init__(self, _ip, _level, _date):
        """
        Constructor

        Args:
            ip ({str}): The entity's ip address
        """     
        self.ip_add = _ip
        self.level = _level
        self.date = _date

    @classmethod
    def create_from_msg(cls, msg):
        """
        The method will create an Event object out of a given binary object.
        :param cls: the Event class pointer
        :type cls: Event class
        :param msg: the binary message to be parsed
        :type msg: bytearray
        :return: an Event object made by the binary message
        :rtype: Event
        """
        print(msg)
        
        level = msg[0]
        ip_add = ".".join([str(i) for i in msg[1:5]])
        
        temp = sum([pow(256, 3-i) * int(msg[5+i]) for i in range(4)])
        today = datetime.datetime.now()

        today_delta = Event.calc_date_param(today)
        today -= datetime.timedelta(milliseconds=today_delta)
        today -= datetime.timedelta(microseconds=today.microsecond)
        
        if today_delta < temp:
            today -= datetime.timedelta(days=1)
        
        date = today + datetime.timedelta(milliseconds=temp)

        a = cls(ip_add, level, date)
        print("created from message: ", a.date)
        return a

    @classmethod
    def create_from_list(cls, event_params):
        """
        The method will create an Event object out of a given list of parameters
        :param cls: the Event class pointer
        :type cls: Event class
        :param event_params: list of attributes to be parsed (Example: ['5.5.5.5', 4, '2021-01-24 16:07:45.029904'])
        :type event_params: list
        :return: an Event object made by the given list
        :rtype: Event
        """
        ip_add = event_params[0]
        level = event_params[1]
        try:
            date = datetime.datetime.strptime(event_params[2], '%Y-%m-%d %H:%M:%S.%f')
        except Exception:
            date = datetime.datetime.strptime(event_params[2], '%Y-%m-%d %H:%M:%S')

        return cls(ip_add, level, date)

    # getters functions
    def get_ip_add(self):
        return self.ip_add
    
    def get_level(self):
        return self.level
    
    def get_date(self):
        return self.date
    
    @staticmethod
    def calc_date_param(time):
        return time.hour * 60*60 * 1000 + time.minute * 60 * 1000 + time.second * 1000 + int(time.microsecond / 1000)

    def calc_date(self):
        """
        This function returns the amount of milliseconds that passed since the start of day until the event's date

        Returns:
            int: hour in milliseconds
        """

        return Event.calc_date_param(self.date)

    def to_packet(self):
        """
        This function builds the binary message of this event for the packet to the global server
        Returns:
            byteAarray: the binary message
        """
        mes = bytearray()  # create empty bytearray
        
        mes.append(self.level)  # add the level of blocking
        
        for i in self.ip_add.split('.'):  # add IP address
            mes.append(int(i))
        
        BASE = 256
        date = self.calc_date()
        vals = []
        while date > 0:
            vals += [date % BASE]
            date //= BASE
        
        if len(vals) < 4:
            vals += [0]*(4-len(vals))

        vals.reverse()

        for val in vals:
            mes.append(val)
            
        return mes
