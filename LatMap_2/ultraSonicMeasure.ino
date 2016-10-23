/*********************************************
sends out a pulse from the ultrasonic sensor
listens for the pulse
returns distance
*/
void ultraSonicMeasure(){
  long duration;
  byte distance;
  
  //pulse timeout (2 times the max range times velocity)
  long timeOut = 2*255*74;

  //set the pin mode
  pinMode(pingPin, OUTPUT);
  //short silence
  digitalWrite(pingPin, LOW );
  delayMicroseconds(2);
  //send out pulse
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW );

  //listen for signal
  //switch the pin mode
  pinMode(pingPin, INPUT);
  //set duration equal to the time
  duration = pulseIn(pingPin, HIGH, timeOut);
  //calculate the distance
  distance =  microsecondsToInches(duration);
    
  //store the value in EEPROM
  store(distance);
}

/**********************************************
converts the time for the pulse to return to a measurment in incehs
passed the pulse time
*/
byte microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch 

  //this is the distance
  long dis = microseconds / 74 / 2;
  //cast into a byte format so it can be saved
  if(dis<254){
    return (byte)dis;
  }
  else { //the pulse timed out
    return 255;
  }
}

/*******************************************************
sotres the measurement
*/
void store(byte distance){
  //check to make sure there is still memory space
  if(curMem<=1016){
    //save the value
    EEPROM.write(curMem, distance);
    //increment the  memory one byte
    curMem+=8;
  }
}



