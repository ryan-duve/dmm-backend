#writeResistance.py
#writeResistance takes in data string returned by DVM and writes resistances to database

import re
def writeResistance(data,password,cur,cnx):
        query = "INSERT INTO slowcontrolreadings (device, raw_reading, measurement_reading) VALUES (%s,%s,%s)"

        entries= [('hfResistance',data,data)]

        cur.executemany(query,entries)
        cnx.commit()
