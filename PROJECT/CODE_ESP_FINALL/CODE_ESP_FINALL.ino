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
    String input = espSerial.readString() + "\n";
    Serial.println(input);
    // espSerial.print("sss");
  }

  // espSerial.write("c");

  if(Serial.available()){
    int inputss = Serial.read();
    Serial.print(inputss);
    espSerial.println("o");
  }
}
