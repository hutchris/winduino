#include <Stepper.h>
#include <Bridge.h>
#include <Process.h>

//This declares variables to use for the motor output
int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int pin4 = 9;

//This declares a variable for the value, passed from python
char steps[5];
char windDir[5];

//This declares the variable to hold previous position
char prev_windDir[5] = "0";

//Creates a motor object. Steps per rev, pins.
Stepper motor(512, pin1, pin2, pin3, pin4);

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication
  Serial.begin(9600);  
  while (!Serial);
  Serial.println("Serial connected...\n");
  //delay(60000);
  //Initialise bridge process. Needs to be done before python script is run
  Serial.println("Starting bridge...\n");
  Bridge.begin();
  //Set the pins as output
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(13,OUTPUT);
  //Sets the speed of steps.
  motor.setSpeed(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Create a process object
  Serial.println("Running script. prev_windDir var is: \n");
  Serial.println(prev_windDir);
  Process p;
  //Run the python script on Linino
  p.begin("python");
  p.addParameter("/mnt/sda1/arduino/winduino/winduino.py");
  p.addParameter(prev_windDir);
  p.run();
  Serial.println("Script complete \n");

  //Retrieve variables from the bridge
  Bridge.get("steps",steps,5);
  Bridge.get("windDir",windDir,5);
  Serial.println("steps variable from bridge:\n");
  Serial.println(steps);
  Serial.println("windDir variable from bridge:\n");
  Serial.println(windDir);
  
  //Change the string variable to an integer
  int steps_int = atoi(steps);

  //if steps_int is not -1 do steps
  if (steps_int != -1)
  {
     //Turn wand to new direction
     motor.step(steps_int);
     //Store wind direction as prev_windDir
     strncpy(prev_windDir,windDir,5);
     Serial.println("strcpy complete. prev_windDir var is now: \n");
     Serial.println(prev_windDir);
     //Blink onboard led for 5 seconds
     digitalWrite(13,HIGH);
     delay(5000);
     digitalWrite(13,LOW);
  }
  //if steps_int is -1 shake the wand and blink the led
  else
  {
    for (int x = 0; x <= 10; x++)
    {
      digitalWrite(13,HIGH);
      motor.step(50);
      digitalWrite(13,LOW);
      motor.step(-50);
    }
  }
  //wait 1 minute
  delay(60000);
}
