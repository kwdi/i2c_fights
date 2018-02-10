#include <Wire.h>
#include <Servo.h>
#define OWN_ADDRESS 1

Servo myservo; 
int pos = 0;
int lets_roll=0;

int winResp = 0; 
void setup() {
  myservo.attach(7);
  Wire.begin(OWN_ADDRESS);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(9600);           // start serial for output
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  //TODO: Respond to REQ 
  //Wait for winner or loop
  delay(200);  

  if (lets_roll==1){
      for (pos = 30; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 30; pos -= 5) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }

   lets_roll=0;   
  }

}

 
void requestEvent(){
  Wire.write(random(1,4));
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)   

  while (1 < Wire.available()) { // loop through all but the last
    int c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  if(x == 7){
    
    Serial.print("slave ");
    Serial.print((int)OWN_ADDRESS);
    Serial.print(" WON!!!"); 
    Serial.println(x);         // print the integer
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    lets_roll=1;
  }
  //TODO: WINNER SEQUENCEs!
}
