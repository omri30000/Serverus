import sqlite3
import Event
import datetime

class DatabaseManager:
    def __init__(self, db_file_name):
        self.db = sqlite3.connect(db_file_name)
        self.db_cursor = self.db.cursor()
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
        sql_statement = "INSERT INTO Users (username, password, computerId) VALUES (\'" + username + "\', \'" + password + "\', " + str(product_id) + ")"
        self.db_cursor.execute(sql_statement)

    def insert_product(self):
        sql_statement = "INSERT INTO Products (joinDate) VALUES (\'" + str(datetime.datetime.now()) + "\')"
        self.db_cursor.execute(sql_statement)

        sql_statement = "SELECT * FROM Products" # WHERE joinDate=\'" + str(datetime.datetime.now()) + "\'"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        for row in rows:
            print(row)
    # --------------------------------------------------------------

    def insert_event(self, event, product_id):
        sql_statement = '''INSERT INTO Events (productId, attackerIp, blockLevel)
        VALUES (''' + str(product_id) + ", \'" + event.get_ip_add() + "\', " + event.get_level() + ")"
        self.db_cursor.execute(sql_statement)


    def get_dangerous_events(self, time, product_id):
        """
        The method will find all the events of level 4 that isn't related to the given user and appeared after a specific time
        :param self: the instance of manager
        :type self: DatabaseManager
        :param time: the minimum approved date of an event
        :type time: Datetime
        :param product_id: the id of the product that needs the data
        :type product_id: int
	    :return: no return value
	    :rtype: None
	    """
        sql_statement = "SELECT * FROM Products WHERE productId != " + str(product_id) + " AND blockLevel = 4"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()



def main():
    a = DatabaseManager("general_db.sqlite")
    a.insert_product()

if __name__ == '__main__':
    main()