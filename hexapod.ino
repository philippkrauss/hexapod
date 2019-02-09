#include <Oscillator.h>
#include <RF24.h>

Oscillator leftLeg;
Oscillator rightLeg;
Oscillator middleLeg;

RF24 radio(7, 8);
const uint64_t receiver_address = 0xA8A8E1F0C6LL;
const byte address[6] = "00001";

typedef struct {
  signed int x;
  signed int y;
  bool axis;
  bool a;
  bool b;
  bool c;
  bool d;
  bool e;
  bool f;
} JoystickValues;

JoystickValues joystickValues;

int cycleDuration = 2000;
int cycleCorrection = 0;
int leftStepAmplitude = 45;
int rightStepAmplitude = 45;

char ackData[33] = "HEXAPOD         LINE2           ";

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1, address);
    radio.setAutoAck(true);
    radio.enableAckPayload();
    radio.enableDynamicPayloads();
    radio.setPALevel(RF24_PA_MIN);
    radio.enableAckPayload();
    radio.writeAckPayload(1, &ackData, sizeof(ackData));
    radio.startListening();

    joystickValues.x = 0;
    joystickValues.y = 0;
    
    leftLeg.attach(4, false);
    rightLeg.attach(2, false);
    middleLeg.attach(3, false);

    //Amplitude
    middleLeg.SetA(10);
    leftLeg.SetA(leftStepAmplitude);
    rightLeg.SetA(rightStepAmplitude);

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
    while (radio.available()) {
        radio.read(&joystickValues, sizeof(JoystickValues));
        radio.writeAckPayload(1, &ackData, sizeof(ackData));
        cycleCorrection = map(joystickValues.y, -512, 512, -1500, 1500);
    }

    middleLeg.SetT(cycleDuration - cycleCorrection);
    rightLeg.SetT(cycleDuration - cycleCorrection);
    leftLeg.SetT(cycleDuration - cycleCorrection);

    int newAmplitude = map(joystickValues.x, -512, 512, -45, 45);
    int leftAmplitude = 45;
    int rightAmplitude = 45;
    if (newAmplitude < 0) {
        rightAmplitude += newAmplitude;
    } else {
        leftAmplitude -= newAmplitude; 
    }

    leftLeg.SetA(leftAmplitude);
    rightLeg.SetA(rightAmplitude);

    middleLeg.refresh();
    leftLeg.refresh();
    rightLeg.refresh();
}