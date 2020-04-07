/*
  LightPatterns
  By: Alvin Tran

  Manipulate a LED and RGB LED with a series of button pushes and an LDR sensor. Demonstrates how a state machine can run a program. 
  
*/
//constants won't change. Used here to set a pin number or set a constant number:
const int Red=12;// the number of the red LED pin
const int Green=33;// the number of the green LED pin
const int Blue=27;// the number of the blue LED pin
const int ledExternal=14;// the number of the external LED light
const int ledInternal=13;// the number of the internal LED light
const int pushButton=A0;// the pin that the button is attached to
const int LDRsensor=A1;// LDR sensor

//Tracks which state the sketch should be on
int buttonPushCounter=0;// counter for the number of button presses
int buttonState=0;// current state of the button
int lastButtonState=0;// previous state of the button
int functionTracker=0;

//Variables to help with timer
unsigned long previousMillis=0;// will store last time LED was updated
const long interval=1000;// interval at which to blink (milliseconds)

//Tracks which RGB LED to turn on
int color=0;//tracks how many loops the sketch has run
int ledState=HIGH;//ledState used to set the LED; set on high first so that ledState will be high on even numbered loops

void setup() {
  // set the digital pin as output:
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);  
  pinMode(Blue, OUTPUT);
  pinMode(ledExternal, OUTPUT);
  pinMode(ledInternal, OUTPUT);
  pinMode(pushButton, INPUT);//Button
  pinMode(LDRsensor, INPUT);//LDR sensor
  Serial.begin(9600);
}

void loop() {  
  int buttonState=digitalRead(pushButton);
  delay(200);// delay to stabilize button

  Serial.println("Start");
  Serial.print("Number of button pushes: ");
  Serial.println(buttonPushCounter);
  
  //compare the buttonState to its previous state
  if(buttonState!=lastButtonState) 
  {
    //if the state has changed, increment the counter
    if(buttonState==1) 
    {
      //if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
    }
    delay(50);// Delay a little bit to avoid bouncing
  }
  
  delay(50);//Delay a little bit to avoid bouncing
  lastButtonState=buttonState;

  functionTracker=buttonPushCounter;

  switch(functionTracker)
  {
    case 1:   
    Serial.println("Introduction");
    Introduction();
    delay(50);
    break;
    
    case 2:
    Serial.println("Sirens");
    Sirens();    
    delay(50);
    break;

    case 3:
    Serial.println("LightAdjust");
    LightAdjust();    
    delay(50);
    break;

    default:      
    Serial.println("keepOff");
    keepOff();
    buttonPushCounter=0;    
    delay(50);
    break;
  }
  
  //None-switch case coding; Rough draft
  /*if(buttonPushCounter==0)//Introduction
  {
    digitalWrite(ledExternal, HIGH);
    digitalWrite(ledInternal, HIGH); 
    digitalWrite(Red, HIGH); 
  }
  else if(buttonPushCounter==1)//Siren: Simulate an emergency siren
  {
     // check to see if it's time to blink the LED; that is, if the difference
     // between the current time and last time you blinked the LED is bigger than
     // the interval at which you want to blink the LED.
     unsigned long currentMillis=millis();
     if(currentMillis-previousMillis>=interval) 
     {
      //Save the last time you blinked the LED
      previousMillis=currentMillis;
      //if clause that checks if the LED is off turn it on and vice-versa:
      if(ledState==LOW) 
      {
        ledState=HIGH;    
        color+=1;//color increments by 1
      }
      else 
      {
        ledState=LOW;
      }
     }
     //If clause that checks the modulo of color
     if(color%6==0)//Check if color fits the condition in sequential order
     {
      digitalWrite(Blue, ledState);   
      color=0;//Reset the counter to allow for RGB pattern  
     }
     else if(color%4==0)
     {
      digitalWrite(ledExternal, HIGH);  
     }
     else if(color%2==0)
     {
      digitalWrite(Red, ledState); 
     }     
    }
    else if(buttonPushCounter==2)
    {
      if(sensorValue<=)
      
    }
    else if(buttonPushCounter==4)
    {
      buttonPushCounter=0;
    }*/
 } 

 void keepOff()
 {
  digitalWrite(Red, LOW);  
  digitalWrite(Green, LOW);
  digitalWrite(Blue, LOW);
  digitalWrite(ledExternal, LOW);
  digitalWrite(ledInternal, LOW);
 }
 void Introduction()//Blink RGB all three colors while keeping LEDs on
 {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis=millis();
  
  if(currentMillis-previousMillis>=interval) 
  {
    //Save the last time you blinked the LED
    previousMillis=currentMillis;
  
    //if clause that checks if the LED is off turn it on and vice-versa:
    if(ledState==LOW) 
    {
      ledState=HIGH;    
      color+=1;//color increments by 1
    }
    else 
    {
      ledState=LOW;
    }     
    
    digitalWrite(ledExternal, HIGH);
    digitalWrite(ledInternal, HIGH);

    //If clause that checks the modulo of color
    if(color%6==0)//Check if color fits the condition in sequential order
    {
      digitalWrite(Blue, ledState);   
      color=0;//Reset the counter to allow for RGB pattern  
    }
    else if(color%4==0)
    {
      digitalWrite(Green, ledState); 
    }
    else if(color%2==0)
    {
      digitalWrite(Red, ledState); 
    }   
  }
 }

 void Sirens()//Simulates sirens by flashing red, blue, and yellow lights
 {
  unsigned long currentMillis=millis();
  if(currentMillis-previousMillis>=interval) 
  {
    //Save the last time you blinked the LED
    previousMillis=currentMillis;
    //if clause that checks if the LED is off turn it on and vice-versa:
    if(ledState==LOW) 
    {
      ledState=HIGH;    
      color+=1;//color increments by 1
    }
    else 
    {
      ledState=LOW;
    }
   }
   
   //If clause that checks the modulo of color
   if(color%6==0)//Check if color fits the condition in sequential order
   {
    digitalWrite(Blue, ledState);
    digitalWrite(ledExternal, ledState);      
    digitalWrite(ledInternal, ledState);   
    color=0;//Reset the counter to allow for RGB pattern  
   }
   else if(color%4==0)
   {
    digitalWrite(ledExternal, ledState);      
    digitalWrite(ledInternal, ledState);   
   }
   else if(color%2==0)
   {
    digitalWrite(Red, ledState); 
    digitalWrite(ledExternal, ledState);      
    digitalWrite(ledInternal, ledState);
   }     
 }

 void LightAdjust()//Adjusts lights according to input from LDR sensor
 {
  int sensorValue=analogRead(LDRsensor);
  
  if(sensorValue<=250)
  {
    digitalWrite(Red, HIGH);     
    digitalWrite(Blue, LOW);      
    digitalWrite(Green, LOW);
    digitalWrite(ledExternal, LOW);    
    digitalWrite(ledInternal, HIGH);      
  }
  else if(sensorValue>250&&sensorValue<2500)
  {
    digitalWrite(Red, LOW);      
    digitalWrite(Blue, HIGH);        
    digitalWrite(Green, LOW);
    digitalWrite(ledExternal, HIGH);    
    digitalWrite(ledInternal, HIGH);      
  }
  else if(sensorValue>=2500)
  {
    digitalWrite(Red, LOW);     
    digitalWrite(Blue, LOW);   
    digitalWrite(Green, HIGH);
    digitalWrite(ledExternal, HIGH);    
    digitalWrite(ledInternal, LOW);
  }
 }
