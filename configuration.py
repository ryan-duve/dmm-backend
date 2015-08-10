#configuration.py
#set up serial and mysql connections

import serial
import mysql.connector

#get password
with open ("password", "r") as myfile:
    password=myfile.read().replace('\n', '')

#mysql config
#http://dev.mysql.com/doc/connector-python/en/connector-python-connectargs.html
config={
        'user':'root',
        'password':password,
        'host':'128.143.100.54',
        'database':'slowcontrols',
}

#start serial
ser = serial.Serial('/dev/ttyS0',
         2400,
         parity=serial.PARITY_NONE,
         rtscts=False,
         bytesize=serial.EIGHTBITS,
         stopbits=serial.STOPBITS_TWO,
         timeout=0,
         xonxoff=True,
         dsrdtr=False)

#start mysql
cnx = mysql.connector.connect(**config) 
cur = cnx.cursor() 
