import datetime

class Rule:
    def __init__(self,entity,level):
        """Constructor

        Args:
            entity ({Entity}): Hostile Entity to block
            level ([{int}]): Anomaly Level
        """        
        self.date = datetime.datetime.now()
        self.mac_add = entity.get_mac_add()
        self.temp = level == 2 #TODO: take away levels from here

    """
    This function returns the parameters for the iptables rule
    Input: none
    Output: the parameters : string
    """
    def write_rule(self):
        """
        This function returns the parameters for the iptables rule

        Returns:
            [str]: the rule parameters
        """        

        return "-m mac --mac-source "+self.mac_add


    """getters functions""" 

    def is_temp(self):
        return self.is_temp
       
    def get_date(self):
        return self.date