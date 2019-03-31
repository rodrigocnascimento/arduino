#include <Arduino.h>
#include <SoftwareSerial.h>
int PIN_7 = 7; // green
int PIN_6 = 6; // red
int PIN_5 = 5; // yellow

SoftwareSerial BtHC05(11, 10); //RX TX
String bltEntry = "";

void setup() {
  Serial.begin(9600);
  BtHC05.begin(9600);
  Serial.println("Gateway bluetooth is open!\nConnect to HC-05 with password 1234");
  BtHC05.println("What color shoul turn ON?");
  
  pinMode(PIN_7, OUTPUT);
  digitalWrite(PIN_7, LOW);

  pinMode(PIN_6, OUTPUT);
  digitalWrite(PIN_6, LOW);

  pinMode(PIN_5, OUTPUT);
  digitalWrite(PIN_5, LOW);
}

void loop() {
  if(BtHC05.available()) {
    bltEntry = BtHC05.readString();
    
    Serial.println(bltEntry);
    if (bltEntry == "green") {
      if (digitalRead(PIN_7) == HIGH) {
        digitalWrite(PIN_7, LOW);
      } else {
        digitalWrite(PIN_7, HIGH);
      }
      digitalWrite(PIN_5, LOW);
      digitalWrite(PIN_6, LOW);
      Serial.println("LED 7");
      BtHC05.println("LED 7");
    } else if (bltEntry == "red") {
      if (digitalRead(PIN_6) == HIGH) {
        digitalWrite(PIN_6, LOW);
      } else {
        digitalWrite(PIN_6, HIGH);
      }
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_5, LOW);
      Serial.println("LED 6");
      BtHC05.println("LED 6");
    } else if (bltEntry == "yellow") {
      if (digitalRead(PIN_5) == HIGH) {
        digitalWrite(PIN_5, LOW);
      } else {
        digitalWrite(PIN_5, HIGH);
      }
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_6, LOW);
      Serial.println("LED 5");
      BtHC05.println("LED 5");
    }
    bltEntry = "";
  }
}