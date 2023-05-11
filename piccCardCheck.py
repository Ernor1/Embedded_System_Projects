import mysql.connector
import serial
import time

ser = serial.Serial('COM19', 9600)
time.sleep(2)
print( ser.readline())
# Connect to the database
conn = mysql.connector.connect(
  host="localhost",
  port=3307,
  user="root",
  password="?dh344440",
  database="webapp"
)
c = conn.cursor()
while 1:
    uid = ser.readline().decode('utf-8').strip()
    
    if uid == "This card was lastly detected."or uid == "READING THE CARD UNIQUE ID:" or uid=="********************":
        continue
    
    c.execute("SELECT * FROM unique_ids WHERE uid=%s", (uid,))
    result = c.fetchone()
    if result is None:
        ser.write('0'.encode())
        print("ID doesn't exist database: {}".format(uid))
    else:
        ser.write('1'.encode())
        print("ID already exists in database: {}".format(uid))
