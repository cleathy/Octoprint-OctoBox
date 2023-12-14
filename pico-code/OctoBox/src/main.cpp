#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <LittleFS.h>
#include <FastLED.h>


#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/flash.h"
#include "hardware/adc.h"
#include "hardware/irq.h"


volatile bool settingsFileLock = false; // shared lock variable



//Multicore functions
//Pause Other Core
void pauseOtherCore(){
  rp2040.idleOtherCore();
}
//Resume Other Core
void resumeTheOtherCore(){
  rp2040.resumeOtherCore();
}
//Restart Core1
void restartCore(){
  rp2040.restartCore1();
}
//Send data to other core via FIFO
bool sendToOtherCore(uint32_t data){
  return rp2040.fifo.push_nb(data);
}

//Send data via Serial USB
void SerialSend(uint32_t data){
  Serial.println(data);
}

void waitUntillFileIsUnlocked(bool fileLock){
  while(fileLock){
    //Wait untill file is unlocked
  }
}


// First core code
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
  delay(5000);
   //LittleFS.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  //Check if there is a message from the other core
  if (rp2040.fifo.available() > 0)
  {
    uint32_t data = rp2040.fifo.pop();
}

  //Serial recieve
  if (Serial.available() > 0) {
    uint32_t data = Serial.read();
  }

}




// Second core code
void setup1() {
  //Second core setup
  // put your setup code here, to run once:
}

void loop1() {
  // Second core loop
  // put your main code here, to run repeatedly:

  //Check if there is a message from the other core
  if (rp2040.fifo.available() > 0)
  {
    uint32_t data = rp2040.fifo.pop();
  }


}