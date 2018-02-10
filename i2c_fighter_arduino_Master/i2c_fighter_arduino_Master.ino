

#include <Wire.h>
#define PAPER 1
#define SCISSORS 2
#define ROCK 3
#define NUM_CONTESTANTS (2+1)

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
  contestant1=random(1,NUM_CONTESTANTS);
  contestant2=random(1,NUM_CONTESTANTS);
  while(contestant1==contestant2){
    contestant2=random(1,NUM_CONTESTANTS);
    Serial.print("c1 ");
    Serial.println(contestant1);
    Serial.print("c2 ");
    Serial.println(contestant2);
  }
  

}
void StartGame(){
  Wire.requestFrom(contestant1, 1);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    contResp1 = Wire.read(); // receive a byte as character
  }

    Serial.print(contestant1);
    Serial.print(" chose ");
    switch (contResp1){
      case 1: 
        Serial.println("paper"); 
        break;
      case 2: 
        Serial.println("scissors"); 
        break;
      case 3: 
        Serial.println("rock");
        break;
    }
  Wire.requestFrom(contestant2, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    contResp2 = Wire.read(); // receive a byte as character
  }

    Serial.print(contestant2);
    Serial.print(" chose ");
    switch (contResp2){
      case 1: 
        Serial.println("paper"); 
        break;
      case 2: 
        Serial.println("scissors"); 
        break;
      case 3: 
        Serial.println("rock");
        break;
    }
  
  //delay(100);
}

void loop() {
  Serial.println("LOOP START");

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Generating Players ");
  ContGen();
  Serial.println("Requesting weapons ");
  StartGame();
  while(contResp1==contResp2 && contResp1!=0 ){
      Serial.println("Same Weapons chosen, REDO!");
      StartGame();
  }
  
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
    default:
      break;   
  }

  
  Wire.beginTransmission(winner);
  Wire.write(7); //7 defines a lucky number so we send that as a response to the winner
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("----------------------Winner is : ");
  Serial.println(winner);
  delay(500);
 
}
