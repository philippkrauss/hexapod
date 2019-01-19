# hexapod
An arduino based hexapod, see https://www.instructables.com/id/Hexapoduino-tiny-hexapod-3D-printed-Arduino-cont/

Hardware, baught all at aliexpress:

- 3x Servo 9g, 1,24 €
- Arduino Nano, 1,81 €
- nrf24l01, 0,69 €

## Setup
### Install ArduSnake library

```
cd lib
git clone git@github.com:Obijuan/ArduSnake.git
mv ArduSnake ArduSnake2
mv ArduSnake2/ArduSnake ArduSnake
rm -rf ArduSnake2
```

### Install RF24 library

`git clone git@github.com:nRF24/RF24.git`
