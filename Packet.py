from scapy.all import *

class Packet:
    def __init__(self, time, pack):
        """
        time: the arrival time of the packet
        all_data: the whole data of the packet
        """
        if Ether in pack:
            self.source_mac = pack[Ether].src
        else:
            raise Exception("can't create packet")
        
        if IP in pack:
            self.source_IP = pack[IP].src
            self.dest_IP = pack[IP].dst
        else:
            raise Exception("can't create packet")
        
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
                raise Exception("can't create packet")
            
        try:
            self.length = pack.len
            self.data = pack[Raw].load
        except:
            raise Exception("can't create packet")
        
        self.arrival_time = time
    
    def asdict(self):
        return {'source_mac': self.source_mac, 'source_IP': self.source_IP, 'dest_IP': self.dest_IP, 
        'source_port': self.source_port, 'dest_port': self.dest_port, 'protocol': self.protocol, 'length': self.length, 
        'data': self.data, 'arrival_time': self.arrival_time}

