#include <Stepper.h>
#include <Bridge.h>
#include <Process.h>

//This declares variables to use for the motor output
int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int pin4 = 9;

//This declares a variable for the value, passed from python
char steps[4];
char windDir[4];


//This declares the variable to hold previous position
char prev_windDir[4] = "0";

//Creates a motor object. Steps per rev, pins.
Stepper motor(512, pin1, pin2, pin3, pin4);

void setup() {
  // put your setup code here, to run once:
  //Initialise bridge process. Needs to be done before python script is run
  Bridge.begin();
  //Set the pins as output
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(13,OUTPUT);
  //Sets the speed of steps.
  motor.setSpeed(10);
  //This 1 minute delay allows for the wifi to connect.
  delay(60000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Create a process object
  Process p;
  //Run the python script on Linino
  p.begin("python");
  p.addParameter("/mnt/sda1/arduino/winduino/winduino.py");
  p.addParameter(prev_windDir);
  p.run();

  //Retrieve variables from the bridge
  Bridge.get("steps",steps,4);
  Bridge.get("windDir",windDir,4);
  
  //Change the string variable to an integer
  int steps_int = atoi(steps);
  int windDir_int = atoi(windDir);

  //if steps_int is not -1 do steps
  if (steps_int != -1)
  {
     //Turn wand to new direction
     motor.step(steps_int);
     //Store wind direction as prev_windDir
     strcpy(prev_windDir,windDir);
     //Blink onboard led for 5 seconds
     digitalWrite(13,HIGH);
     delay(5000);
     digitalWrite(13,LOW);
  }
  //if steps_int is -1 shake the wand
  else
  {
    for (int x = 0; x <= 10; x++)
    {
      motor.step(50);
      motor.step(-50);
    }
  }
  //wait 5 minutes
  delay(300000);
}
