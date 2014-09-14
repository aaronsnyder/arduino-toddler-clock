/*
 * toddlerClock sketch
 * Sets the color of an RGB LED to either a 'wake' color, or a 'sleep' color.
 * Intended as a coaching tool to help your toddler stay in bed.
 * Requires Time.h for setting the clock: http://playground.arduino.cc/Code/Time
 */

#include <Time.h>
//TODO: make syncing time with computer work...
//#define TIME_MSG_LEN  11
//#define TIME_HEADER  'T'
//#define TIME_REQUEST  7

const int GREEN_LED_PIN = 9;
const int BLUE_LED_PIN = 10;
const int RED_LED_PIN = 11;

const int SLEEP_RED_VALUE = 25;
const int SLEEP_GREEN_VALUE = 25;
const int SLEEP_BLUE_VALUE = 200;

const int WAKE_RED_VALUE = 0;
const int WAKE_GREEN_VALUE = 255;
const int WAKE_BLUE_VALUE = 0;

const int WAKE_HOUR = 6;
const int WAKE_MINUTE = 30;
const int SLEEP_HOUR = 20;
const int SLEEP_MINUTE = 00;

const int INDICATOR_OFF_HOUR = 7;
const int INDICATOR_ON_HOUR = 19;

int greenValue = 0;
int blueValue = 0;
int redValue = 0;

void setup() {
//  TODO: make syncing time with computer work...  
//  Serial.begin(9600);
//  requestClockSync();
//  while(timeStatus() == timeNotSet); 

  setTime(17,29,55,13,9,14);
  
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);  
}

void loop() {
  delay(1000);  

  if(indicatorIsOn()) {
    if(isSleepTime()) {
      redValue = SLEEP_RED_VALUE;
      greenValue = SLEEP_GREEN_VALUE;
      blueValue = SLEEP_BLUE_VALUE;
    } 
    else {
      redValue = WAKE_RED_VALUE;
      greenValue = WAKE_GREEN_VALUE;
      blueValue = WAKE_BLUE_VALUE;
    }		
  }

  analogWrite(GREEN_LED_PIN,greenValue);
  analogWrite(BLUE_LED_PIN,blueValue);
  analogWrite(RED_LED_PIN,redValue);
}

bool isSleepTime() {
  bool sleepCriteriaMet = false;

  if(
  (hour() < WAKE_HOUR)
    || (hour() > SLEEP_HOUR)
    || (hour() == WAKE_HOUR && minute() < WAKE_MINUTE)
    || (hour() == SLEEP_HOUR && minute() >= SLEEP_MINUTE)
    ) {
    sleepCriteriaMet = true;
  }

  return sleepCriteriaMet;
}

bool indicatorIsOn() {
  bool isDuringIndicatorHours = false;

  if(
  (hour() < INDICATOR_OFF_HOUR)
    || (hour() >= INDICATOR_ON_HOUR)
    ) {
    isDuringIndicatorHours = true;
  }

  return isDuringIndicatorHours;
}

//TODO: make syncing time with computer work...
//void requestClockSync() {
//  // if time sync available from serial port, update time
//  while(Serial.available() >= TIME_MSG_LEN){  // time message consists of header & 10 ASCII digits
//    char c = Serial.read();
//    Serial.print(c);  
//    if(c == TIME_HEADER) {      
//      time_t pctime = 0;
//      for(int i=0; i < TIME_MSG_LEN -1; i++){  
//        c = Serial.read();          
//        if(c >= '0' && c <= '9'){  
//          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
//        }
//      }  
//      setTime(pctime); // Sync Arduino clock to the time received on the serial port
//    }  
//  }
//}


