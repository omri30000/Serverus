import sqlite3
import datetime
import hashlib

import config

BLOCK_LEVEL = 5


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
        self.db.close()

    def insert_user(self, username, password):

        # does username exist

        exist = True
        try:
            a = self.get_user_id(username)
        except Exception as e:
            exist = False
        
        if exist:
            raise Exception("user exists")

        product_time = self.__insert_product()

        enc_password = hashlib.md5(password.encode()).hexdigest()
        sql_statement = "SELECT id FROM Products WHERE joinDate=\'" + product_time + "\'"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        sql_statement = "INSERT INTO Users (username, password, productId) VALUES (\'" + username + "\', \'" + \
                        enc_password + "\', " + str(rows[0][0]) + ")"

        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL);")
        print("ok")

        return self.get_user_id(username)

    def check_login(self,username,password):
        enc_password = hashlib.md5(password.encode()).hexdigest()
        sql_statement = "SELECT * from Users WHERE username = '{}' AND password = '{}'".format(username, enc_password)
        self.db_cursor.execute(sql_statement)

        rows = self.db_cursor.fetchall()

        return len(rows) == 1
    
    def get_user_id(self, username):
        # should add try-except
        sql_statement = "SELECT id FROM Users WHERE username = \'" + username + "\';"
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()
        return rows[0][0]

    def get_all_rules(self, user_id):
        """
        The function will provide all the data of Rule table in the db
        :return: all the data of Rule table
        :rtype: list(list(rule_id, rule_data))
        """
        sql_statement = "SELECT id, attackerIP FROM Events WHERE productId = " + str(self.get_product_id(user_id))
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        for i in range(len(rows)):
            rows[i] = list(rows[i])

        return rows

    def get_all_events(self, user_id):
        """
        The function will provide all the Events of a specific product in the db
        :param user_id: the identifier of a user
        :type user_id: int
        :return: all the events of the product of the given user
        :rtype: list(list(event date, attacker ip, block level))
        """
        sql_statement = "SELECT date, attackerIP, blockLevel FROM Events WHERE productId = " + str(self.get_product_id(user_id))
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        for i in range(len(rows)):
            rows[i] = list(rows[i])

        return rows

    def get_anomalies(self, user_id):
        """
        The function will provide all the amount of anomalies per day
        :param user_id: the identifier of a user
        :type user_id: int
        :return: the amount of anomalies per day
        :rtype: Dict(date: amount of anomalies)
        """
        sql_statement = "SELECT date FROM Events WHERE productId = " + str(self.get_product_id(user_id))
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()
        for i in range(len(rows)):
            if rows[i][0] is not None:
                rows[i] = rows[i][0].split(' ')[0]  # take only the day as key (21-03-13)
            else:
                rows[i] = None

        count = {}
        for j in rows:
            if j is not None:
                if j in count.keys():
                    count[j] += 1
                else:
                    count[j] = 1

        return count

    def get_product_id(self, user_id):
        sql_statement = "SELECT productId FROM Users WHERE id = " + str(user_id) + ";"
        self.db_cursor.execute(sql_statement)
        return self.db_cursor.fetchall()[0][0]

    def add_rule(self, user_identifier, rule):
        if self.__is_rule_exist(user_identifier, rule):
            return None

        product_id = self.get_product_id(user_identifier)

        sql_statement = "INSERT INTO Events (productId, attackerIP, blockLevel, date) VALUES ({},'{}',{},'{}')"\
            .format(str(product_id), rule, str(BLOCK_LEVEL), str(datetime.datetime.now()))
        
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL);")

    def remove_rule(self, user_identifier, rule_identifier):
        product_id = self.get_product_id(user_identifier)
        sql_statement = "DELETE FROM Events WHERE id = " + str(rule_identifier) + \
                        " AND productId = " + str(product_id)

        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL);")

    def __insert_product(self):
        d = str(datetime.datetime.now())
        sql_statement = "INSERT INTO Products (joinDate, lastSeenDate) VALUES (\'" + d + \
                        "\',\'1970-01-01 00:00:00.000000\')"
        self.db_cursor.execute(sql_statement)
        self.db.commit()
        self.db_cursor.execute("PRAGMA wal_checkpoint(FULL);")
        return d

    def __is_rule_exist(self, user_identifier, ip_address):
        """
        The function will check if a user already holds a rule with a specific data
        :param user_identifier: the id of the user in the database
        :type user_identifier: int
        :param ip_address: the data of a rule
        :type ip_address: str
        :return: True or False if the rule exists
        :rtype: bool
        """
        product_identifier = self.get_product_id(user_identifier)
        sql_statement = "SELECT id FROM Events WHERE productId = {} AND attackerIP = '{}';"\
            .format(str(product_identifier), ip_address)
        self.db_cursor.execute(sql_statement)
        rows = self.db_cursor.fetchall()

        return len(rows) > 0


def main():
    a = DatabaseManager(db_file_name=config.DB_FILE_NAME)
    # a.insert_user("dghjg", "12341")
    # print(a.is_rule_exist(6, "45.23.12.24"))
    a.add_rule(11, "1.2.31.1")


if __name__ == '__main__':
    main()
