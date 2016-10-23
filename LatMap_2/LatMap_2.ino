/**********************************
 * LatMap_2
 * 
 * ECE 210 Final Project
 * C3C Nathan Ruprecht
 * C3C Brian Yarbrough
 * 
 * Hardware:
 * 1 Ultrasonic sensor
 * 2 DC Motors
 * 1 Ardunio Uno
 * 1 Push Button
 * 1 9V battery
 * 
 * General Description
 * Measures distances in a 360 degree radius
 * Stores values to onboard EEPROM
 * Outputs Values to Serial monitor
 * 
 * Values are then independently procesed and mapped with MatLab
 * 
 * 10 December 2013
 * /////////////////////////////////////
 * Documentation:
 * Ultrasonic code referencd from http://www.arduino.cc/en/Tutorial/Ping
 * 
 *///////////////////////////////////

//NOTE! the Arduino EEPROM has a lifespan of only 100,000 read/writes
//do not read and write unnecesarily
#include <EEPROM.h>

//motor pins
const int mLeft = 11;
const int mRight = 10;
//button pin
const int btn = 8;
//constant for the pin
const int pingPin = 7;

//current memory index
int curMem = 0;

/***********************************
 * The entire program is run from setup
 * After initial setup, the program waits for a button push before taking measurments
 * On the second button push, it will output the values to the serial monitor
 * These values can then be processed for a 2D map
 */
void setup(){
  //set pinmodes
  pinMode(mRight, OUTPUT);
  pinMode(mLeft, OUTPUT);
  pinMode(btn, INPUT);

  //begin the serial output
  Serial.begin(9600);

  delay(5);

  //wait for button push to begin
  while(digitalRead(btn)==LOW){
    //empty loop
  }

  //USER PUSHES BUTTON//

  delay(1500);
  //begin taking measurments

  //power on the motors
  analogWrite(mRight, 180);
  analogWrite(mLeft, 180);

  //current runtime of the program
  int start = millis();

  //run for 3.2 seconds (~1 rotation)
  while(millis()<start+3200){
    //take measurements
    ultraSonicMeasure();
  }

  //turn off motors
  digitalWrite(mRight, LOW);
  digitalWrite(mLeft, LOW);

  delay(50);

  //USER PUSHES BUTTON//

  //wait for button push
  while(digitalRead(btn)==LOW){
    //empty loop
  }

  //print the data to the computer
  outputData();
} 


/******************************************************
 * Outputs the stored EEPROM data to the serial monitor on the screen
 */
void outputData(){
  int i;
  for(i = 0; i<44*8; i+=8){
    //read the value
    byte value = EEPROM.read(i);
    //print the value
    Serial.println(value);
  }
}

//no loop - code only runs once
void loop(){
}








