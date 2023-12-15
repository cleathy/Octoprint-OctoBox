#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <LittleFS.h>
//#include <FastLED.h>


#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/flash.h"
#include "hardware/adc.h"
#include "hardware/irq.h"


volatile bool settingsFileLock = false; // shared lock variable for settings file



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


//LittleFS functions
//Open file to read or write
File openFile(String fileName, bool write){
  
  if(fileName == ""){
    Serial.println("No filename given");
  }

  else if(!LittleFS.exists(fileName)){
    Serial.println("File does not exist");
  }
  
  else if(LittleFS.exists(fileName)){
    while(settingsFileLock){
      //Wait untill file is unlocked
    }
    settingsFileLock = true;
    //Open file
  LittleFS.begin();
  File file = LittleFS.open(fileName, write ? "w" : "r");
  //Check if file opened
  if (!file) {
    Serial.println("Failed to open file for reading");
  }
  else if(file){
    Serial.println("File opened");
  return file;
  }
  }
  else{
    Serial.println("Something went wrong");
}
  return File();
}

//Close file
void closeFile(File file, String fileName){
  //Close file
  file.close();
  //Unlock file
  settingsFileLock = false;
  LittleFS.end();
}

//Read file
String readFile(String fileName){
  File file = openFile(fileName, false);
  String fileContent = "";
  if(file){
    while(file.available()){
      fileContent += (char)file.read();
    }
  }
  closeFile(file, fileName);
  return fileContent;
}

//Overwrite file with LittleFS
void writeFile(String fileName, String data){
  File file = openFile(fileName, true);
  if(file){
    file.print(data);
  }
  closeFile(file, fileName);
}


// First core code
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
  delay(5000);
   //Should start by transmitting the firmware version to the raspberry pi

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