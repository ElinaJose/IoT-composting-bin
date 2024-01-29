#include<Servo.h>
#define SensorPin A0 
float sensorValue = 0; 
int trig=8;
int echo=9;
int dt=10;
int pos = 0;
Servo servo; //servo pin 11, closes the bin when ultrasonic detects
Servo servo_10; //servo pin 10, rotate compost

//pushbutton to start / stop one cycle of servo motor
int buttonState = 0;
int lastButtonState = 0;
int buttonPushCounter = 0;

//int distance,duration;
void setup() {
  // put your setup code here, to run once:
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
Serial.begin(9600);
servo.attach(11);
pinMode(2, INPUT); //push button ready to accept input
pinMode(LED_BUILTIN, OUTPUT);
//servo at pin 10 for rotating the compost
servo_10.attach(10, 500, 2500);
}

void loop() {

  for (int i = 0; i <= 100; i++) //coding soil moisture sensor
 { 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(1); 
 } 
 sensorValue = sensorValue/100.0; 
 Serial.println(sensorValue); 
 delay(30);


if (calc_dis()<100)//if ultrasonic detects wastes in 100cm
{
  for (int i=0;i<=540;i++)
  {
    servo.write(i);
    delay(1);
  }
  delay(100);
  for (int i=540;i>=0;i--)
  {
    servo.write(i);
    delay(1);
  }
  delay(100);
}
  
  // read the pushbutton input pin
  buttonState = digitalRead(2);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH, then the button
      // went from off to on
      buttonPushCounter += 1;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
      
      //codes for: if pushbutton ON, servo pin 10 also on
      // sweep the servo from 0 to 180 degrees in steps
  	  // of 1 degrees
  		for (pos = 0; pos <= 180; pos += 1) {
      // tell servo to go to position in variable 'pos'
    	servo_10.write(pos);
      // wait 15 ms for servo to reach the position
    	delay(15); // Wait for 15 millisecond(s)
  		}
  		for (pos = 180; pos >= 0; pos -= 1) {
      // tell servo to go to position in variable 'pos'
    	servo_10.write(pos);
      // wait 15 ms for servo to reach the position
    	delay(15); // Wait for 15 millisecond(s)
  		}
    } else {
      // if the current state is LOW, then the button
      // went from on to off
      Serial.println("off");
    }
    // delay a little bit to avoid debouncing
    delay(5); // Wait for 5 millisecond(s)
  }
  // save the current state as the last state, for
  // the next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every four button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the devision of two numbers
  if (buttonPushCounter % 4 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

//This code is written to calculate the DISTANCE using ULTRASONIC SENSOR

int calc_dis()
{
  int duration,distance;
  digitalWrite(trig,HIGH);
  delay(dt);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}