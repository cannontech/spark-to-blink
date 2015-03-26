/*
  Spark to Blink
  Eric Schmit
  2015
  Based on work by Kostas Kokoras' Inductive Spark Plug Sensor
  http://kokoraskostas.blogspot.com/2013/12/arduino-inductive-spark-plug-sensor.html
*/

const int ignitionPin = 2;
const int ignitionInterrupt = 0;
const int ledPinRight = 13;
const int ledPinLeft = 12;

unsigned long lastPulseTime = 0;
unsigned long rpm = 0;
unsigned long count = 0;

// put your setup code here, to run once:
void setup() 
{
  pinMode(ignitionPin, INPUT);
  pinMode(ledPinRight, OUTPUT);
  pinMode(ledPinLeft, OUTPUT);
  
  attachInterrupt(ignitionInterrupt, &blinkLED, RISING);
}

//called when the circuit detects a spark
void blinkLED()
{
  count++;
  
  //decide if we should light the left/right (front/back) cylinder leds
  0 == count % 2 ? blinkBank(ledPinRight) : blinkBank(ledPinLeft);
  
  //avoid overrun
  if(count > 4000000000)
  {
    count = 0;
  }
}

void blinkBank(int pin)
{
    digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);                 // wait for a time
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
    delay(20);                 // wait for a time
}

// put your main code here, to run repeatedly: 
void loop() 
{
  noInterrupts();
  int(rpm);  //really just a no-op
  interrupts();  
}
