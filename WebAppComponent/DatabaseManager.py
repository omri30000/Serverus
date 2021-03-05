import sqlite3
import datetime
import hashlib

class DatabaseManager:
    def __init__(self, db_file_name):
        self.db = sqlite3.connect(db_file_name, check_same_thread=False)
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
        self.db.close()

    def insert_user(self, username, password):
        product_time = self.__insert_product()

        enc_password = hashlib.md5(password.encode()).hexdigest()
        sql_statement = "SELECT * FROM Products WHERE joinDate=\'" + product_time + "\'"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        sql_statement = "INSERT INTO Users (username, password, productId) VALUES (\'" + username + "\', \'" + \
                        enc_password + "\', " + str(rows[0][0]) + ")"
    
        print(sql_statement)

        self.db_cursor.execute(sql_statement)
        self.db.commit()

        return self.get_user_id(username)

    def check_login(self,username,password):
        enc_password = hashlib.md5(password.encode()).hexdigest()
        sql_statement = "SELECT * from Users WHERE username = '{}' AND password = '{}'".format(username, enc_password)
        self.db_cursor.execute(sql_statement)

        rows = self.db_cursor.fetchall()

        return len(rows) == 1
            
        
        
    
    def get_user_id(self,username):
        #should add try-except
        sql_statement = "SELECT id FROM Users WHERE username = \'" + username + "\';"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()
        return rows[0]

    def __insert_product(self):
        d = str(datetime.datetime.now())
        sql_statement = "INSERT INTO Products (joinDate, lastSeenDate) VALUES (\'" + d + \
                        "\',\'1970-01-01 00:00:00.000000\')"
        self.db_cursor.execute(sql_statement)

        return d


def main():
    a = DatabaseManager(db_file_name="database.sqlite")
    a.insert_user("dghjg", "12341")


if __name__ == '__main__':
    main()
