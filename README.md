# winduino
Arduino Yun project to display the wind direction on a 3D printed device

Work in process. 

Components:

Files:
- winduino.py
 - python script that gets the wind direction for your city and passes it to the Arduino sketch. Sits on the SD card of the Arduino Yun
- conf.txt
 - Config file to site beside python script. Contains an API key for http://openweathermap.org and city id. JSON format.
- winduino.ino
 - Sketch file to be uploaded to the Arduino by the IDE.
Physical:
- Arduino Yun device
- 3D printed casing. Purchase here: http://shpws.me/OfC3
- 3D printed wand. Purchase here: http://shpws.me/OfBZ


