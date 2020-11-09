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
            self.data = pack[Raw].load
        except:
            self.length = 0
            self.data = ''
        
        self.arrival_time = time

        print("create successfuly")
    
    def asdict(self):
        return {'source_mac': self.source_mac, 'source_IP': self.source_IP, 'dest_IP': self.dest_IP, 
        'source_port': str(self.source_port), 'dest_port': str(self.dest_port), 'protocol': self.protocol, 'length': str(self.length), 
        'data': self.data, 'arrival_time': str(self.arrival_time)}

