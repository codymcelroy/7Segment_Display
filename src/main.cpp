#include <Arduino.h>

int dataPin = 4; // data pin
int latchPin = 5; // RCLK latchpin Register Clock (on the rising edge of this clock the data is moved to the output register)
int clockPin = 6; // SRCLK shift bits into the register, must be high
//SRCLR - Master Reset pin: set all pins to 0 at once (RESET = LOW) ... not set in this example and pulled permanently high 

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600); 
}

byte code = B00000000;
int arraycount = 0;

int myArray[] = {
// ALL ROTATION IS COUNTER CLOCKWISE
//FILLING THE MIDDLE
8,0,8,0
,8,8,8,72,8,72,8,72,72,72,73,72,73,72,73,73,73
,72,73,72,73,72,72,72,8,72,8,72,8,8,8
//READY START GO
,0,8,0,8,0,0,0,64,64,64,0,0,0,64,64,64,0,0,0
//STARTING FULL CIRCLE @16
,16
,24	,28	,30	,31	,63	,47	,39	,35	,33	,32
,48	,56	,60	,62	,63	,31	,15	,7	,3
//FULL CIRCLE PATTERN 
	,1,33,49,57,61,63,62,30,14,6,2,3,35,51,59,63,61,60,28,12,4,6,7,39,55,63,59,57,56,24,8,12,14,15,47,63,55,51,49,48,16,24,28,30,31,63,47,39,35,33,32
  ,48,56,60,62,63,31,15,7,3
//SINGLE CIRCLE PATTERN
,1,32,16,8,4,2
//TRANSITION - STARTING @2
,3	,35	,51	,59	
//MISSING 1 CIRCLE
,61,62,31,47,55,59
//TRANSITION TO CLEAR  CIRCLE - STARTING @59
,57,56,24,8,0
//WHEN CLEAR THE LOOP STARTS OVER AGAIN
,0,0,0
};


void switch_on() {

  digitalWrite(latchPin, HIGH);   // Move shift register to output
    delay(1);
  digitalWrite(latchPin, LOW);    // Reset shift register output
 
}

void loop() {

for (int i =0; i < sizeof myArray/sizeof myArray[0]; i++)
{
  int code = myArray[i];

  shiftOut(dataPin, clockPin, MSBFIRST, code);
  switch_on(); // Move register content to output
  switch_on();
  delay(300);
  Serial.println(code);
  }
}



