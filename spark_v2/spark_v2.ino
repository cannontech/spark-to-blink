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

const unsigned int pulsesPerRev = 1;

unsigned long lastPulseTime = 0;
unsigned long rpm = 0;
unsigned long count = 0;

// put your setup code here, to run once:
void setup() 
{
  //Serial.begin(9600);  
  pinMode(ignitionPin, INPUT);
  pinMode(ledPinRight, OUTPUT);
  pinMode(ledPinLeft, OUTPUT);
  
  //attachInterrupt(ignitionInterrupt, &ignitionIsr, RISING);
  attachInterrupt(ignitionInterrupt, &blinkLED, RISING);
}

void blinkLED()
{
  count++;
  
  if(count % 2 == 0)
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(20);              // wait for a second
  }
  else
  {
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(20);              // wait for a second
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
    delay(20);              // wait for a second
  }
  
  if(count > 4000000000)
  {
    count = 0;
  }
}

void ignitionIsr()
{
  unsigned long now = micros();
  unsigned long interval = now - lastPulseTime;
	
  //if it has been more than 5ms
  if (interval > 5000)
  {
    //the longer the interval, the slower the engine is running
    rpm = 60000000UL/(interval * pulsesPerRev);
    lastPulseTime = now;
  }  
}

// put your main code here, to run repeatedly: 
void loop() 
{
  noInterrupts();
  rpm_to_disp=int(rpm);
  interrupts();  
}
