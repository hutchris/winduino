import sys
import json
import time
import urllib2

#add arduino bridge module to sys path
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
	except:
		pass
	if resp != 200:
		time.sleep(10)
		count += 1

if resp == 200:
	weatherData = json.loads(urlobj.read())
	windDir = weatherData['wind']['deg']
else:
	windDir = -1

#creates a bridge object
bricli = BridgeClient()

#Pass variables to the bridge memory
bricli.put('windDir',windDir)

