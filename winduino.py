import sys
import json
import time
import urllib2

sys.path.insert(0, '/usr/lib/python2.7/bridge/')
from bridgeclient import BridgeClient

with open("conf.txt","r") as confFile:
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
	except urllib2.HTTPError, err:
		resp = err.code
	except:
		time.sleep(10)
	if resp != 200:
		time.sleep(10)
		count += 1

if resp == 200:
	weatherData = json.loads(urlobj.read())
	windDir = weatherData['wind']['deg']

