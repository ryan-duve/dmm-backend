#!/usr/bin/python
import sys
import re
import thread,time
from configuration import *
from writeResistance import *

#initialize converter
from converter import *
c = DMMConverter()

print "Reading resistance: press Ctrl+C to stop"
#http://ubuntuforums.org/showthread.php?t=1514035#post_9488318
data=""
try:
	while True:
		time.sleep(0.1)#give dmm time to broadcast (also, don't kill CPU)

		#data comes in 8 bits then 6 bits (in two transmissions)
		data+=ser.read(ser.inWaiting())

		if(len(data)>0):#assuming we got something

			if len(data)==8: #wait for second part of message
				continue

			if len(data)==14: #entire 14-bit message has arrived
				encoded_data=data.encode("hex")
				c.convert(encoded_data.decode("hex"))
				#print "converted_data =",c.convertedvalue
				writeResistance(c.convertedvalue,password,cur,cnx)
	
				#clear data_buffer
				data=""
				ser.flushInput()
	
			else: #something funky happened, clear the buffer
				#print "clearing buffer"
				ser.flushInput()
				data=""

except KeyboardInterrupt:
	print "\nStopping data acquistion"

#kill mysql
cur.close()
cnx.close()
