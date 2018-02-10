

#include <Wire.h>
#define PAPER 1
#define SCISSORS 2
#define ROCK 3

int contestant1;
int contestant2;
int contResp1;
int contResp2;
int winner;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(LED_BUILTIN, OUTPUT);
  
}

byte x = 0;

void ContGen(){
  
  contestant1=random(1,3);
  contestant2=random(1,3);
  while(contestant1==contestant2){
    contestant2=random(1,2);
    Serial.println("c1");
    Serial.print(contestant1);
    Serial.println("c2");
    Serial.print(contestant2);
    Serial.println("GEN WHILE");
  }
  

}
void StartGame(){
  Wire.requestFrom(contestant1, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    contResp1 = Wire.read(); // receive a byte as character
  }

  Wire.requestFrom(contestant2, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    contResp2 = Wire.read(); // receive a byte as character
  }
  delay(100);
}

void loop() {
    Serial.println("LOOP START");

  digitalWrite(LED_BUILTIN, LOW);
  ContGen();
  Serial.println("GEN NUM");
  StartGame();
    Serial.println("GAMESTART");

  
  while(contResp1==contResp2){
      StartGame();  
  }
    Serial.println(contestant2);
    Serial.println(contestant1);

  

  switch(contResp1){
    case PAPER:
       if(contResp2 == SCISSORS) winner=contestant2;
       else winner = contestant1;
       break;
    case SCISSORS:
       if(contResp2 == ROCK) winner=contestant2;
       else winner = contestant1;
       break;
    case ROCK:
       if(contResp2 == PAPER) winner=contestant2;
       else winner = contestant1;
       break;   
  }

  Wire.beginTransmission(winner);
  Wire.write(7); //7 defines a lucky number so we send that as a response to the winner
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("winner");
  Serial.print(winner);
  delay(500);
  

}
