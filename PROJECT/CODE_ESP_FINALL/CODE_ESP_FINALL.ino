#include <SoftwareSerial.h>

SoftwareSerial espSerial(14, 12); //13-15 // rx-tx

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(espSerial.available()){
    String input = espSerial.readString();
    Serial.print(input);
    // espSerial.print("sss");
  }

  // espSerial.write("c");

  if(Serial.available()){
    String inputss = Serial.readString();
    Serial.print(inputss);
    espSerial.print(inputss + '\r');
  }
}
