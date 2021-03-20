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

        sql_statement = "Update Products set lastSeenDate = '{}' +  WHERE computerId = {}".format(now_date,computer_id)
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
        sql_statement = "INSERT INTO Events (productId, attackerIp, blockLevel, date) VALUES (" + str(
            product_id) + ", \'" + event.get_ip_add() + "\', " + str(event.get_level()) + ", \'" + str(
            event.get_date()) + "\')"
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL)")

        sql_statement = "SELECT id FROM Events WHERE date = '{}'".format(str(event.get_date()))
        rows = self.db_cursor.fetchall()
        print(rows)
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
        sql_statement = "SELECT attackerIp, blockLevel, date FROM Events WHERE productId != " + str(product_id) + " AND blockLevel = 4"
        self.db_cursor.execute(sql_statement)

        rows = self.db_cursor.fetchall()
        events = []
        for i in range(0, len(rows)):
            single_event = Event.Event.create_from_list(list(rows[i]))
            if time is None or time < single_event.get_date():
                events += [single_event]

        return events

"""
def main():
    a = DatabaseManager("general_db.sqlite")

    
"""

if __name__ == '__main__':
    main()
