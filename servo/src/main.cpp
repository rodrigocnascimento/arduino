#include <Arduino.h>
#include <Servo.h>
Servo servo;

#define BTN_RED 7
#define BTN_GREEN 6
#define LED_GREEN 13
#define LED_RED 12
#define BTN_OFF 5
#define POT_PIN A0

void setup()
{
    pinMode(BTN_RED, INPUT_PULLUP);
    pinMode(BTN_GREEN, INPUT_PULLUP);
    pinMode(BTN_OFF, INPUT_PULLUP);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
}

void turnOffLeds()
{
    for (int angle = 0; angle <= 180; angle++)
    {
        servo.write(angle);
        delay(10);
    }
    servo.detach();
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
}

void turnServoClockwise()
{
    if (digitalRead(BTN_RED) == LOW)
    {
        for (int angle = 0; angle <= 180; angle++) 
        {
            servo.write(angle);
            delay(10);
        }
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        servo.detach();
    }
}

void turnServoAntiClockwise()
{
    if (digitalRead(BTN_GREEN) == LOW)
    {
        for (int angle = 180; angle >= 0; angle--)
        {
            servo.write(angle);
            delay(10);
        }
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
        servo.detach();
    }
}

void turnOff()
{
    if (digitalRead(BTN_OFF) == LOW)
    {
        if (servo.read() == 0)
        {
            turnOffLeds();
        }
        else
        {
            turnServoClockwise();
            turnOffLeds();
        }
    }
}

void potServo()
{
    int pot_val;
    pot_val = analogRead(POT_PIN);
    pot_val = map(pot_val, 0, 1023, 0, 180);
    servo.write(pot_val);
    delay(15);
}


void loop()
{
    servo.attach(9);
    turnServoClockwise();
    turnServoAntiClockwise();
    turnOff();
    potServo();
}