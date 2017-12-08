# -*- coding: utf-8 -*-

import time;
import urllib.request;
import pandas;
from pandas import DataFrame;
from bs4 import BeautifulSoup;
from urllib.error import URLError;

def readPage(url):
    do = True
    fail = 0
    ssid = ""
    seg = ""
    formula = ""
    
    while do:
        print (url)
        try:
            response = urllib.request.urlopen(
                url,
                timeout = 2
            )
            
            html = response.read()
            html = html.decode('utf-8')
            soup = BeautifulSoup(html)
            table = soup.findAll('table')
            tableId = table[5]
            tableIndex = table[6]
            tableFormula = table[7]
            ssid = tableId.find('td').text.strip()
            seg = tableIndex.find('tt').text
            tds = tableFormula.findAll('td')
            
            flag = False
            
            for td in tds:
                pretest = td.find('font')
                if (flag == True):
                    formula = td.text
                    break
                if (pretest):
                    leftstr = pretest.text
                    if (leftstr == "FORMULA"):
                        flag = True
                        
            if (flag == False):
                fail = 0
                return ("", "", "")

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
        if (fail > 25):
            fail = 0
            output = open("/home/africamonkey/Downloads/oeis/fail.txt", "a")
            output.write(url)
            output.write("\n")
            output.close()
            return ("", "", "")
    fail = 0
    return (ssid, seg, formula)

taskIds = pandas.read_csv(
        "/home/africamonkey/Downloads/oeis/allNeed.csv"
        ).taskId

input = open("/home/africamonkey/Downloads/oeis/lastans.txt", "r")
lastans = int(input.read())
input.close()

input = open("/home/africamonkey/Downloads/oeis/end.txt", "r")
end = int(input.read())
input.close()

ssids = []
segs = []
formulas = []

for i in range(lastans + 1, end):
    url = 'http://oeis.org/%s' % taskIds[i]
    print ('No.%d' % i)
    _ssid = ""
    _seg = ""
    _formula = ""
    _ssid, _seg, _formula = readPage(url)
    if (_ssid != ""):
        ssids.append(_ssid)
        segs.append(_seg)
        formulas.append(_formula)
        
    result = DataFrame({
                'ssid': ssids,
                'seg': segs,
                'formula': formulas
            })

    result.to_csv(
            "/home/africamonkey/Downloads/oeis/result.csv",
            mode='a',
            header=False,
            )
    ssids = []
    segs = []
    formulas = []
    
    output = open("/home/africamonkey/Downloads/oeis/lastans.txt", "w")
    output.write(str(i))
    output.close()
    