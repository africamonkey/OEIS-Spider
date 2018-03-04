# -*- coding: utf-8 -*-

import time;
import urllib.request;
import pandas;
from pandas import DataFrame;
from bs4 import BeautifulSoup;
from urllib.error import URLError;
import json

def readPage(num_id, url):
	do = True
	fail = 0
	
	while do:
		print (url)
		try:
			response = urllib.request.urlopen(
				url,
				timeout = 2
			)
			
			jsonBytes = response.read()
			jsonString = jsonBytes.decode('utf-8')
			res = json.loads(jsonString) 
			for top_res in res:
				if (top_res == 'results'):
					for sec_res in res[top_res]:
						final_res = json.dumps(sec_res, indent = 4)
						outp = open("data/%s.txt" % (num_id), "w")
						outp.write(final_res)
						outp.close()
						return
			return

		except URLError as e:
			print (e)
			fail = fail + 1
			if (e.reason == 'Not Found'):
				fail = 0
				return ("", "", "")
			if (fail < 10):
				time.sleep(1)
			else:
				time.sleep((fail - 9) * 10)
		except Exception as e:
			fail = fail + 1
			if (fail < 10):
				time.sleep(1)
			else:
				time.sleep((fail - 9) * 10)
			print (e)
		else:
			fail = fail + 1
			if (fail < 10):
				time.sleep(1)
			else:
				time.sleep((fail - 9) * 10)
			do = False
		if (fail > 20):
			fail = 0
			output = open("fail.txt", "a")
			output.write(url)
			output.write("\n")
			output.close()
			return
	fail = 0
	return

taskIds = pandas.read_csv(
		"allNeed.csv"
		).taskId

input = open("lastans.txt", "r")
lastans = int(input.read())
input.close()

input = open("end.txt", "r")
end = int(input.read())
input.close()


for i in range(lastans, end):
	url = 'http://oeis.org/search?q=%s&fmt=json' % taskIds[i]
	print ('No.%d' % i)
	readPage(taskIds[i], url)
	
	output = open("lastans.txt", "w")
	output.write(str(i))
	output.close()
	
