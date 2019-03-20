/*
 Originally wirtten by David LE GALL on 29/08/2017
 With great help from Tatiana GRANGE
 */


const int buttonPin = 10;                                       // The pin where the button is attached
int buttonState = 0;                                            // a boolean where to store the state of the button
int Counter = 0;                                                // a counter that will be incremented or decremented

unsigned long TimeAtPress=0;                                    // a variable where to store the time at which the button is pressed
unsigned long TimeAtRelease=0;                                  // a variable where to store the time at which the button is realeased
int TimePressed=0;

const int TimeShortPress=400;                                   // between 0 and 500ms the press will be considered a short or quick press
const int TimeLongPress=TimeShortPress*3;                       // between 0 and 500ms the press will be considered a long press

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  buttonState = digitalRead(buttonPin);                         // read the state of the pushbutton value:

  
  
  if (buttonState == HIGH) {                                    //Check if the pushbutton is pressed.if it is, the buttonState is HIGH:
      TimeAtPress=millis();                                     //Memorise when the button was pressed
      while (buttonState == HIGH){                              //infinite loop while the button is pressed
        buttonState = digitalRead(buttonPin);                   //re-read the state of the button
        Serial.println("Waiting for button to be released");    //for debugging purposes, when this is displayed, the code is waiting for you to release the button
                                                                // IF too long, break; Besoin de checker comment qu'c'ey break. 
        TimePressed=millis()- TimeAtPress ;                     //Calculate Elapsed Time                                  // TimePressed=millis()- TimeAtPress;
        // Need to check if timepressed > Timelong
        if (TimePressed > TimeLongPress )
        {
          Serial.println("Waited too long");
          delay(1000);
          break;
        }

        
        }
      Serial.println("Button released");

      TimePressed = millis() - TimeAtPress ;                    //Calculate Elapsed Time
        if (TimePressed <= TimeShortPress )                     //first, check if the time was shorter than a ShortPress
          {   
           Counter = Counter+1;                                 //Increment counter if button i dashed
          } 

        else if( TimePressed <= TimeLongPress)
          {
            Counter= Counter-1 ;
          }   
          
  } 
  Serial.println(Counter);
}
