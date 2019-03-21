# ArduinoHourglass
A little object that uses two 8x8 LED Matrix and a tilt switch to display time.

It is thought as a Chess/Go Game clock : it keeps track of time for 2 players, after each move, it has to be flipped.
Different time presets can be chosen when initialising : 15mn, 30mn, 45mn, 1h. 


This is an image of the wiring i used, if the hourglass behaves with 'gravity' upside-down, try rotating the tilt switch ;)

![This is the wiring](https://raw.githubusercontent.com/Zblay/ArduinoHourglass/master/HourGlass.png)

### Parts List
* 1x Arduino UNO 
* 2x 8x8 LED Matrix (with MAX7219)
* 1x TiltSwitch 
* 1x 220Ohm Resistor
 
#### Sources and inspiration

I was inspired by a version of the Arduino Hourglass by Fabrizio Branca.
https://www.youtube.com/watch?v=U-vmEOuy348
https://github.com/fbrnc/Arduino_Hourglass


I like the way this displays time, i think i might use it as a total time selector display :
https://create.arduino.cc/projecthub/funnypolynomial/matrixclock-1d2e75?ref=tag&ref_id=clocks&offset=28

#### Project History
* 10/04/2018  First working version of the hourglass
* 19/03/2018  I have adapted the hourglass design to work as a chess/go game clock : Both opponents have the same amount of time at the beginning and when the hourglass is rotated, it switches between the time left for each of them. The code works but hasn't been cleaned yet.
* 21/03/2019 I have added a way to select the total time for each player you want to choose, the presets are 15, 30, 45 and 60 minutes, The code is now much cleaner, still not perfect but all in english and working. It's time to make a video.



 <iframe width="560" height="315"
src="https://www.youtube.com/embed/MUQfKFzIOeU" 
frameborder="0" 
allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" 
allowfullscreen></iframe>
