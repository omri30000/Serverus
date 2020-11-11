import datetime

class Rule:
    def __init__(self,entity,level):
        self.date = datetime.datetime.now()
        self.mac_add = entity.get_mac_add()
        self.temp = level == 2 #TODO: take away levels from here


    def write_rule(self):
        return "-m mac --mac-source {}"%self.mac_add

    def is_temp(self):
        return self.is_temp
       
    def get_date(self):
        return self.date