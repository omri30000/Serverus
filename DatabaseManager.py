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

    def insert_product(self):
        sql_statement = "INSERT INTO Products (joinDate) VALUES (\'" + str(datetime.datetime.now()) + "\')"
        print(sql_statement)
        self.db_cursor.execute(sql_statement)

        # sql_statement = "SELECT * FROM Products WHERE joinDate=" + str(datetime.datetime.now()) 
        # self.db_cursor.execute(sql_statement)


    def insert_event(self, event, product_id):
        sql_statement = '''INSERT INTO Events (productId, attackerIp, blockLevel)
        VALUES (''' + str(product_id) + ", \'" + event.get_ip_add() + "\', " + event.get_level() + ")"
        self.db_cursor.execute(sql_statement)



def main():
    a = DatabaseManager("general_db.sqlite")
    a.insert_product()
    a.insert_product()
    a.insert_product()

if __name__ == '__main__':
    main()