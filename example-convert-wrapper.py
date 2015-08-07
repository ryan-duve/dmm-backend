#!/usr/bin/python
from ctypes import cdll
lib = cdll.LoadLibrary('./libconvert-14bits-to-useful-info.so')

class Foo(object):
	def __init__(self):
		self.obj = lib.DMMConverter_new()

	def convert(self,string):
		lib.DMMConverter_convert(self.obj,string)


f = Foo()
f.convert("132030475d6e788090a0b2c4d0e8".decode("hex"))
