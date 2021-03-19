import datetime
import Event
# This is the Rule class, which handles iptables rules

class Rule:
    def __init__(self,event):
        """Constructor

        Args:
            entity ({Event}): The Hostile event
            temp ({bool}): Is the rule temporally
        """        
        self.date = datetime.datetime.now()
        self.event = event

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

        #return "-m mac --mac-source "+self.ent.get_mac_add()
        return " -s " + self.event.get_ip_add()
        


    """getters functions""" 

    def is_temp(self):
        return self.event.get_level() == 2
       
    def get_date(self):
        return self.date