from scapy.all import *
import datetime

class Packet:
    def __init__(self, pack):
        """
        The initializer of the Packet object. allow the user to create a Packet and initial it. 
        :param self: the instance of Packet
        :type self: Packet
        :param pack: the packet from scapy in it's basic format
        :type pack: scapy.packet
	    :return: no return value
	    :rtype: None
	    """

        microseconds =int(pack.time*1000000 - int(pack.time) * 1000000 )

        self.arrival_time = datetime.datetime.fromtimestamp(pack.time)

        if(self.arrival_time.microsecond == 0 and self.arrival_time.microsecond !=microseconds):
            self.arrival_time += datetime.timedelta(microseconds=  microseconds) 

        self.length = len(pack)  # the packet's size in bytes

        if IP in pack:
            self.source_IP = pack[IP].src
            self.dest_IP = pack[IP].dst
            self.protocol = "IP"
        else:
            self.source_IP = ""
            self.dest_IP = ""
            self.protocol = ""
        
        if pack.haslayer(ARP):
            self.source_port = "NONE"
            self.dest_port = "NONE"  
        elif TCP in pack:
            self.source_port = str(pack[TCP].sport)
            self.dest_port = str(pack[TCP].dport)
            self.protocol = "TCP"
        elif UDP in pack:
            self.source_port = str(pack[UDP].sport)
            self.dest_port = str(pack[UDP].dport)
            self.protocol = "UDP"
        else:
            self.source_port = "NONE"
            self.dest_port = "NONE"                
        
        self.source_mac = pack.src
        self.dest_mac = pack.src
        
        if self.source_port == "NONE":
            if pack.haslayer(ARP):
                self.source_IP = pack[ARP].psrc
                self.dest_IP = pack[ARP].pdst
                self.protocol = "ARP"
            elif pack.haslayer(ICMP):
                self.protocol = "ICMP"

        try:
            self.data = pack[Raw].load.decode()
            print("##data##")
            print(type(self.data))
            print("########")
        except:
            self.data = ''
        

        self.__activate()


    def __activate(self):
        """
        The method will operate an activation on the packet's size
        the function is the linear function: y = (1/MAX_SIZE_MEASURED)*x for 0 <= x < 1000
        :param self: the instance of Packet
        :type self: Packet
	    :return: None
	    :rtype: None
        """
        MAX_SIZE_MEASURED = 5000.0
        
        if self.length > MAX_SIZE_MEASURED:  # the size is very big
            self.length = 1
        else:
            self.length = (1 / MAX_SIZE_MEASURED) * self.length


    def asdict(self):
        """
        The function will cast this Packet instance to a dictionary that the csv writer can write
        :param self: the instance of Packet
        :type self: Packet
	    :return: a dictionary represents the current Packet object
	    :rtype: Dict
	    """
        return {'source_mac': self.source_mac, 'source_IP': self.source_IP, 'dest_IP': self.dest_IP, 
        'source_port': str(self.source_port), 'dest_port': str(self.dest_port), 'protocol': self.protocol, 'length': str(self.length), 
        'data': self.data, 'arrival_time': str(self.arrival_time)}


    def cast_to_sql_statement(self):
        """
        The function will cast this Packet instance to a SQL statement that will be written to the Database.
        :param self: the instance of Packet
        :type self: Packet
	    :return: a sql insert statement represents the current Packet object
	    :rtype: string
	    """

        statement = '''INSERT INTO packets (source_mac,destination_mac,source_IP,dest_IP,source_port,
                        dest_port,protocol,length,data,arrival_time)''' + " VALUES (\'" + self.source_mac + "\',\'" + self.dest_mac + "\',\'" + self.source_IP + "\',\'" + self.dest_IP + \
        "\',\'" + self.source_port + "\',\'" + self.dest_port + "\',\'" + self.protocol + "\'," + str(self.length) + \
        ",\'" + self.data + "\',\'" + str(self.arrival_time) + "\')"
        
        return statement
