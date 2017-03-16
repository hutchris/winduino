#!/usr/bin/python2.7

import os
import sys
import json
import time
import urllib2

#add arduino bridge module to sys path
sys.path.insert(0, '/usr/lib/python2.7/bridge/')
from bridgeclient import BridgeClient

prev_windDir = int(sys.argv[1])

fileDir = os.path.dirname(os.path.realpath(__file__))
confPath = os.path.join(fileDir,"conf.txt")

with open(confPath,"r") as confFile:
	conf = json.loads(confFile.read())

apiKey = conf['apiKey']
cityid = conf['city']

url = "http://api.openweathermap.org/data/2.5/weather?id={id}&APPID={key}".format(id=cityid,key=apiKey)

resp = -1
count = 0

while resp != 200 and count < 4:
	try:
		urlobj = urllib2.urlopen(url)
		resp = urlobj.getcode()
	except:
		pass
	if resp != 200:
		time.sleep(10)
		count += 1

def numberOfSteps(previous,current):
	diff = current-previous
	if abs(diff) > 180:
		steps = (360 - max(previous,current)) + min(previous,current)
		if current > previous:
			steps = steps - (2 * steps)
	else:
		steps = diff
	steps = int(steps * (512.0/360.0))
	return(steps)

if resp == 200:
	weatherData = json.loads(urlobj.read())
	windDir = weatherData['wind']['deg']
	steps = numberOfSteps(prev_windDir,windDir)
else:
	windDir = prev_windDir
	steps = -1

#creates a bridge object
bricli = BridgeClient()

#Pass variables to the bridge memory
bricli.put('steps',str(steps))
bricli.put('windDir',str(windDir))
