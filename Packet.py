from scapy.all import *

class Packet:
    def __init__(self, time, pack):
        """
        The initializer of the Packet object. allow the user to create a Packet and initial it. 
        :param self: the instance of Packet
        :type self: Packet
        :param time: the time when the packet arrived
        :type time: datetime.datetime
        :param pack: the packet from scapy in it's basic format
        :type pack: scapy.packet
	    :return: no return value
	    :rtype: None
	    """
        if Ether in pack:
            self.source_mac = pack[Ether].src
        else:
            raise Exception("can't create packet - Ether")
        
        if IP in pack:
            self.source_IP = pack[IP].src
            self.dest_IP = pack[IP].dst
        else:
            raise Exception("can't create packet - IP")
        
        try:
            self.source_port = pack[UDP].sport
            self.dest_port = pack[UDP].dport
            self.protocol = "UDP"
        except:
            try: 
                self.source_port = pack[TCP].sport
                self.dest_port = pack[TCP].dport
                self.protocol = "TCP"
            except:
                raise Exception("can't create packet - TCP/UDP")
            
        try:
            self.length = pack.len
            self.data = pack[Raw].load.decode()
            print("##data##")
            print(type(self.data))
            print("########")
        except:
            self.length = 0
            self.data = ''
        
        self.arrival_time = time


    

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

        statement = '''INSERT INTO packets (source_mac,source_IP,dest_IP,source_port,
                        dest_port,protocol,length,data,arrival_time)''' + " VALUES (\'" + self.source_mac + "\',\'" + self.source_IP + "\',\'" + self.dest_IP + \
        "\'," + str(self.source_port) + "," + str(self.dest_port) + ",\'" + self.protocol + "\'," + str(self.length) + \
        ",\'" + self.data + "\',\'" + str(self.arrival_time) + "\')"
        
        return statement
