#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define _SSID "H04_L1_2.4G"          // Your WiFi SSID
#define _PASSWORD "happymk01"      // Your WiFi Password
#define REFERENCE_URL "https://da-1-15997-default-rtdb.europe-west1.firebasedatabase.app/"  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);


#include <SoftwareSerial.h>

SoftwareSerial espSerial(14, 12); //13-15 // rx-tx

const int maxParts = 3; // Maximum number of parts we expect
String stringParts[maxParts];
int intParts[maxParts];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(espSerial.available()){
    String input = espSerial.readStringUntil('\r\n');
    // Serial.print(input);
    const char *data = input.c_str();
    if(data[0] == 'd' && data[1] == 't' && data[2] == ':'){
      if(data[3] == 'r' && data[4] == 't' && data[5] == ':'){
        int dt_ng = (data[6] - '0') * 10 + (data[7] - '0');
        firebase.setInt("data/temperature/realtime", dt_ng);
        Serial.println("temprature real");
      }
      else if(data[3] == 'l' && data[4] == 't' && data[5] == ':'){
        int lt_ng = (data[6] - '0') * 10 + (data[7] - '0');
        firebase.setInt("data/temperature/limit", lt_ng);
        Serial.println("temprature limit");
      }
      else if(data[3] == 'r' && data[4] == 'a' && data[5] == ':'){
        String dt_alarm = input.substring(6, input.length());
        splitString(dt_alarm, '-', stringParts, maxParts);
        for (int i = 0; i < maxParts; i++) {
          intParts[i] = stringParts[i].toInt();
        }
        firebase.setInt("data/alarm/eat/hh", intParts[0]);
        firebase.setInt("data/alarm/eat/pp", intParts[1]);
        firebase.setInt("data/alarm/eat/ss", intParts[2]);
        Serial.println("alarm eat");
      }
    }
  }

  if(Serial.available()){
    String inputss = Serial.readString();
    Serial.print(inputss);
    espSerial.print(inputss + '\r');
  }
}

int decToBcd(int val) {
    return ((val / 10 * 16) + (val % 10));
}

void splitString(String str, char delimiter, String* resultArray, int maxParts) {
  int startIndex = 0;
  int endIndex = 0;
  int partIndex = 0;

  while (endIndex < str.length() && partIndex < maxParts) {
    endIndex = str.indexOf(delimiter, startIndex);
    if (endIndex == -1) {
      endIndex = str.length();
    }

    resultArray[partIndex] = str.substring(startIndex, endIndex);
    partIndex++;
    startIndex = endIndex + 1;
  }
}