# winduino
Arduino Yun project to display the wind direction on a 3D printed device

Components:

Files:
- winduino.py
 - python script that gets the wind direction for your city and passes it to the Arduino sketch. Sits on the SD card of the Arduino Yun
- conf.txt
 - Config file, in same directory as python script. Contains an API key for http://openweathermap.org and city id. JSON format.
- winduino.ino
 - Sketch file to be uploaded to the Arduino Yun

Physical:
- Arduino Yun device
- Stepper Motor: https://www.adafruit.com/product/858
- Motor driver: https://www.adafruit.com/product/807
- 3D printed casing. Purchase here: http://shpws.me/OfC3
- 3D printed wand. Purchase here: http://shpws.me/OfBZ
- Wires and what not

Wiring diagram:
https://learn.adafruit.com/assets/2495

![alt tag](/Images/IMG_0589.JPG)

