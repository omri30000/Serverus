import Entity

class Log():
    
    
    def __init__(self, log_path, overwrite = False):
        self.file_path = log_path

        try:
            if overwrite:
                self.log_file = open(log_path, 'w')
            else:
                self.log_file = open(log_path, 'a')
        except:
            raise Exception("couldn't create log")

    def __del__(self):
        self.log_file.close()


    def add_block_record(self, entity, level):
        st = "Entity in IP address " + entity.get_ip_add() + ", is blocked in blocking level " + str(level) + "!\n"
        self.log_file.write(st)


    def add_unblock_record(self, entity):
        st = "Entity in IP address " + entity.get_ip_add() + ", is unblocked!\n"
        self.log_file.write(st)

    def add_error_record(self, exep):
        st = "an error has occoured: " + exep + "\n"
        self.log_file.write(st)
