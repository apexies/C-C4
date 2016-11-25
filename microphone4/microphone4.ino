/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
#include "config.h"
const int sampleWindow = 100; // Sample window width in mS 
unsigned int sample;
int sendRate = 5000;
int prevsample;
int thresholdmedium = 600;


const int numReadings = 50;              // Take average of every 50 readings
int readings[numReadings];               // readings from analog input
int readIndex = 0;                       // index of current reading
int total = 0;                           // running total
int average = 0;                         // the average

AdafruitIO_Feed *Microphone = io.feed("Microphone");
 
void setup() {
 // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
}
}
void loop() {
    io.run();
    
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 500 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

  total = total - readings[readIndex];
  readings[readIndex] = analogRead(peakToPeak);       // read from peak to peak calculation
  total = total + readings[readIndex];                  // add the reading to the total
  readIndex = readIndex + 1;                          // advance to the next position in the array

  if (readIndex >= numReadings) {                     // if we're at the end of the array...
    readIndex = 0;                                   // ...wrap around to the beginning:
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer
   Serial.print("sending -> ");
   Serial.println(average);
    delay(1);        // delay in between reads for stability
    Microphone->save(average);                         // save average peak-peak amplitude to the 'Microphone' feed on Adafruit IO
  
  prevsample=sample;                              //save microphone state for next comparison: 
}

