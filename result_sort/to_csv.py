import pandas
from pandas import DataFrame
import json

def readPage(task):


taskIds = pandas.read_csv(
		"../prepare/allNeed.csv"
		).taskId


ssids = []
segs = []
formulas = []

for i in taskIds:
	_ssid = ""
	_seg = ""
	_formula = ""
	_ssid, _seg, _formula = readPage(i)
	ssids.append(_ssid)
	segs.append(_seg)
	formulas.append(_formula)

result = DataFrame({
		'ssid': ssids,
		'seg': segs,
		'formula': formulas
		})

result.to_csv(
		"result.csv",
		mode = 'w',
		header = False,
		)
