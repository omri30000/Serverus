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


    def add_block_record(self, ip_add, level):
        st = "Entity in IP address " + str(ip_add) + ", is blocked in blocking level " + str(level) + "!\n"
        self.log_file.write(st)
        self.log_file.flush()

    def add_unblock_record(self, ip_add):
        st = "Entity in IP address " +ip_add + ", is unblocked!\n"
        self.log_file.write(st)
        self.log_file.flush()


    def add_error_record(self, exep):
        st = "an error has occoured: " + exep + "\n"
        self.log_file.write(st)
        self.log_file.flush()

