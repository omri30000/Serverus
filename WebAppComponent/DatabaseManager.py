import sqlite3
import datetime


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

        sql_statement = "SELECT * FROM Products WHERE joinDate=\'" + product_time + "\'"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        sql_statement = "INSERT INTO Users (username, password, productId) VALUES (\'" + username + "\', \'" + \
                        password + "\', " + str(rows[0][0]) + ")"

        self.db_cursor.execute(sql_statement)

        sql_statement = "SELECT * FROM Users WHERE id = (SELECT MAX(id) FROM Users)"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        self.db.commit()
        return rows[0][0]

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
