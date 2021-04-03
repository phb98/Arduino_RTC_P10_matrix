#include <Arduino.h>
#include <RTClib.h>
#include "gpio.h"
#include <SPI.h>
#include "matrix.h"
RTC_DS3231 my_rtc;
void setup() {
  matrix_begin();
  Serial.begin(115200);
  if(!my_rtc.begin()){
    Serial.println("RTC init fail");
    while(1); // infinity loop here
  }
  
}

void loop() {

}