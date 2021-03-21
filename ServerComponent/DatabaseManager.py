import sqlite3
import Event
import datetime


class DatabaseManager:
    def __init__(self, db_file_name):
        self.db = sqlite3.connect(db_file_name, check_same_thread=False)
        self.db_cursor = self.db.cursor()
        self.db_cursor.execute('pragma journal_mode=wal;')
        print("Opened DB successfully")

    def __del__(self):
        """
        The destructor of the DatabaseManager object
        :param self: the instance of manager
        :type self: DatabaseManager
        :return: no return value
        :rtype: None
        """
        self.db.commit()
        self.db.close()

    # -----------to be moved to the http server---------------------
    def insert_user(self, username, password, product_id):
        sql_statement = "INSERT INTO Users (username, password, computerId) VALUES (\'" + username + "\', \'" + \
                        password + "\', " + str(product_id) + ")"
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL)")


    def insert_product(self):
        sql_statement = "INSERT INTO Products (joinDate) VALUES (\'" + str(datetime.datetime.now()) + "\')"
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL)")


        sql_statement = "SELECT * FROM Products"  # WHERE joinDate=\'" + str(datetime.datetime.now()) + "\'"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        for row in rows:
            print(row)

    # --------------------------------------------------------------

    def set_last_date(self,computer_id):
        """
        This function sets the new last seen date of a product
        :param self: the instance of manager
        :type self: DatabaseManager
        :param: computer_id: the id of the requested product
        :type computer_id: int
        :return:No return value
        """
        
        now = datetime.datetime.now()
        now_date = now.strftime("%Y-%m-%d %H:%M:%S.%f")

        sql_statement = "Update Products set lastSeenDate = '{}' WHERE id = {}".format(now_date,computer_id)
        self.db_cursor.execute(sql_statement)


    def get_last_date(self,computer_id):
        """
        The method returns the last time the product accessed the server
        :param self: the instance of manager
        :type self: DatabaseManager
        :param computer_id: the id of the product
        :type event: int
        :return: the date of the last access
        :rtype: datetime.datetime
        """
        sql_statement = "SELECT lastSeenDate FROM Products WHERE computerId = " + str(computer_id)
        self.db_cursor.execute(sql_statement)

        if len(rows) != 1:
            raise Exception("couldn't find computer id")

        rows = self.db_cursor.fetchall()

        time = datetime.datetime.strptime(list(rows[0][0]), '%Y-%m-%d %H:%M:%S.%f')
        return time

    def insert_event(self, event, product_id):
        """
        The method will insert a new event to the database
        :param self: the instance of manager
        :type self: DatabaseManager
        :param event: the event to be inserted
        :type event: Event
        :param product_id: the id of the product that inserts the event
        :type product_id: int
        :return: nothing
        :rtype: None
        """
        sql_statement = "INSERT INTO Events (productId, attackerIp, blockLevel, date, data) VALUES (" + str(
            product_id) + ", \'" + event.get_ip_add() + "\', " + str(event.get_level()) + ", \'" + str(
            event.get_date()) + "\', \'" + event.get_ip_add() + "\')"
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL)")

        
        sql_statement = "SELECT id FROM Events WHERE date = '{}'".format(str(event.get_date()))
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()
        #todo cancel action
        event_id = rows[0][0]

        if event.get_level() > 1:
            if event.get_level() < 4:  # 2 or 3
                self.__insert_block(product_id, event_id)

            elif event.get_level() == 4:
                sql_statement = "SELECT id FROM Products"
                self.db_cursor.execute(sql_statement)

                temp = self.db_cursor.fetchall()
                all_products_ids = [temp[i][0] for i in range(0, len(temp))]

                for single_id in all_products_ids:
                    if not self.__is_block_exists(single_id,event.get_ip_add()):
                        self.__insert_block(single_id, event_id)

    def __insert_block(self, product_id, event_id):
        """
        The method will insert a new block to the database
        :param self: the instance of manager
        :type self: DatabaseManager
        :param product_id: the identifier of the product that the block should relate to
        :type product_id: int
        :param event_id: the identifier of the event that the block should relate to
        :type event_id: int
        :return: nothing
        :rtype: None
        """
        sql_statement = "INSERT INTO Blocks (productId, eventId) VALUES (" + str(product_id) + ", " + str(event_id) + ")"
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL)")


    def get_dangerous_events(self, product_id, time=None):
        """
        The method will find all the events of level 4 that isn't related to the given user and appeared after a specific time
        :param self: the instance of manager
        :type self: DatabaseManager
        :param time: the minimum approved date of an event
        :type time: Datetime
        :param product_id: the id of the product that needs the data
        :type product_id: int
        :return: list of the relevant events
        :rtype: list[Event]
        """
        
        return self.get_rules_by_level_and_time(product_id, time, 4)
    
    def get_rules_by_level_and_time(self,product_id,time,level):
        sql_statement = "SELECT attackerIP, date FROM Events INNER JOIN Blocks ON Blocks.eventId = Events.Id WHERE Events.productId != {} AND blockLevel = {} AND Blocks.productId = {}".format(product_id,str(level),product_id)
        #sql_statement = "SELECT attackerIP, date FROM Events INNER JOIN Blocks ON Blocks.eventId = Events.Id WHERE Events.productId != {} AND blockLevel = {} AND Blocks.productId = {} AND Events.date  > {}".format(product_id,str(level),product_id,str(time))

        
        self.db_cursor.execute(sql_statement)

        rows = self.db_cursor.fetchall()

        events = []
        for i in range(0, len(rows)):
            rows[i] = list(rows[i])
            single_event = Event.Event(rows[0],level,rows[1])
            if time is None or time < single_event.get_date():
                events += [single_event]

        return events

    def __is_block_exists(self,product_id,ip_to_block):
        """
        This function checks if a block to an ip is already exists to this product in the database.
        Args:
            product_id (int): id of the product
            ip_to_block (str): The ip of the hostile entity 

        Returns:
            if the block exists: bool
        """
        sql_statement = "SELECT * from Blocks INNER JOIN Events ON Blocks.eventId = Events.id WHERE attackerIP = '{}'".format(ip_to_block)
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()
        return len(rows) >0




def main():
    a = DatabaseManager("../database.sqlite")

    
    a.insert_event(Event.Event("5.5.5.5", 4, datetime.datetime.now()), 3)
    a.insert_event(Event.Event("5.5.5.5", 4, datetime.datetime.now()), 3)
    a.insert_event(Event.Event("100.100.100.100", 3, datetime.datetime.now()), 11)
    a.insert_event(Event.Event("101.101.101.101", 4, datetime.datetime.now()), 11)
    
    print(a.get_dangerous_events(5, datetime.datetime.now()))


if __name__ == '__main__':
    main()
