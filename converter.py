#!/usr/bin/python
import ctypes
lib = ctypes.cdll.LoadLibrary('./libconvert-14bits-to-useful-info.so')
lib.DMMConverter_convert.restype=ctypes.c_double

class DMMConverter(object):
	def __init__(self):
		self.obj = lib.DMMConverter_new()

	def convert(self,string):
		self.convertedvalue = 0.0
		self.convertedvalue = lib.DMMConverter_convert(self.obj,string)


#f = DMMConverter()
#f.convert("13273d475d677e8995a0b0c4d0e8".decode("hex"))
