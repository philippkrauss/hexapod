#include <Servo.h>
#include <Oscillator.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Oscillator leftLeg;
Oscillator rightLeg;
Oscillator middleLeg;

RF24 radio(7, 8);


int cycleDuration = 2000;
int stepAmplitude = 45;

void setup() {
    Serial.begin(9600);
    radio.begin();
    if (radio.isChipConnected()) { 
        Serial.println("Chip is connected");
    } else {
        Serial.println("connection error!");
    }
    
    leftLeg.attach(4, false);
    rightLeg.attach(2, false);
    middleLeg.attach(3, false);

    //Amplitude
    middleLeg.SetA(10);
    leftLeg.SetA(stepAmplitude);
    rightLeg.SetA(stepAmplitude);

    //offsets to adapt to errors in assembly.
    middleLeg.SetO(-5);
    rightLeg.SetO(0);
    leftLeg.SetO(0);

    middleLeg.SetT(cycleDuration);
    rightLeg.SetT(cycleDuration);
    leftLeg.SetT(cycleDuration);

    //phase difference
    middleLeg.SetPh( DEG2RAD( 90 ));
    rightLeg.SetPh( DEG2RAD( 0 ));
    leftLeg.SetPh( DEG2RAD( 0 ));
}

void loop() {
    middleLeg.refresh();
    leftLeg.refresh();
    rightLeg.refresh();


}