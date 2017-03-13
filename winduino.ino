#include <Stepper.h>
#include <Bridge.h>
#include <Process.h>

//This declares variables to use for the motor output
int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int pin4 = 9;

//This declares a variable for the bridge values, passed from python
char windDir[10];

//This declares the variable to hold previous position
int prev_windDir_int = 0;

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
  p.runShellCommand("python /mnt/sda1/arduino/winduino/winduino.py");

  //Wait for script to finish
  delay(4000);

  //Retrieve variables from the bridge
  Bridge.get("windDir",windDir,10);

  //Change the string variables to integers
  int windDir_int = atoi(windDir);

  //if windDir_int is not -1:
  if (windDir_int != -1)
  {
    int tosteps = max(prev_windDir_int  
  }
  //get number of steps to make
  //do steps
  //save windDir as previous

  //else if windDir_int is -1:
  //do shake
  
}
