import sqlite3
import Event
import datetime

class DatabaseManager:
    def __init__(self, db_file_name):
        self.db = sqlite3.connect(db_file_name)
        self.db_cursor = self.db.cursor()


    def insert_product(self):
        sql_statement = '''INSERT INTO Products (joinDate)
        VALUES (''' + str(datetime.datetime.now()) + ")"
        self.db_cursor.execute(sql_statement)

        sql_statement = "SELECT * FROM Products WHERE joinDate=" + str(datetime.datetime.now()) 
        self.db_cursor.execute(sql_statement)


    def insert_event(self, event, product_id):
        sql_statement = '''INSERT INTO Events (productId, attackerIp, blockLevel)
        VALUES (''' + str(product_id) + ", \'" + event.get_ip_add() + "\', " + event.get_level() + ")"
        self.db_cursor.execute(sql_statement)

