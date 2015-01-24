/*
  Spark to Blink
  Eric Schmit
  2015
  Based on work by Kostas Kokoras' Inductive Spark Plug Sensor
  http://kokoraskostas.blogspot.com/2013/12/arduino-inductive-spark-plug-sensor.html
*/

const int ignitionPin = 2;
const int ignitionInterrupt = 0;
const int ledPin = 13;

const unsigned int pulsesPerRev = 1;

unsigned long lastPulseTime = 0;
unsigned long rpm = 0;

// put your setup code here, to run once:
void setup() 
{
  Serial.begin(9600);  
  pinMode(ignitionPin, INPUT);
  pinMode(ledPin, OUTPUT);  //led on pin13
  
  //attachInterrupt(ignitionInterrupt, &ignitionIsr, RISING);
  attachInterrupt(ignitionInterrupt, &blinkLED, RISING);
}

void blinkLED()
{
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(10);              // wait for a second
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
