# ArduinoHourglass
10/04/2018 A little object that uses two 8x8 LED Matrix and a tilt switch to display time.
Code is commented in French. This is an image of the wiring i used, if the hourglass behaves with 'gravity' upside-down, try rotating the tilt switch ;)

![This is the wiring](https://raw.githubusercontent.com/Zblay/ArduinoHourglass/master/HourGlass.png)

## Parts List
1x Arduino UNO 
2x 8x8 LED Matrix (with MAX7219)
1x TiltSwitch 
1x 220Ohm Resistor

## 19/03/2018  I have adapted the hourglass design to work as a chess/go game clock : 
Both opponents have the same amount of time at the beginning and when the hourglass is rotated, it switches between the time left for each of them.
The code works but hasn't been cleaned yet. 

## Sources and inspiration

I was inspired by a version of the Arduino Hourglass by Fabrizio Branca.
https://www.youtube.com/watch?v=U-vmEOuy348
https://github.com/fbrnc/Arduino_Hourglass


I like the way this displays time, i think i might use it as a total time selector display :
https://create.arduino.cc/projecthub/funnypolynomial/matrixclock-1d2e75?ref=tag&ref_id=clocks&offset=28
