import sqlite3
import Event

class DatabaseManager:
    def __init__(self, db_file_name):
        self.db = sqlite3.connect(db_file_name)

    def insert_event(self, event):
        '''
        INSERT INTO Events (productId, attackerIp, blockLevel)
        VALUES (1,"5.5.5.5", 3)
        '''
        pass