#include <Arduino.h>
#include <RTClib.h>
#include "gpio.h"
#include <SPI.h>
#include "matrix.h"
RTC_DS3231 my_rtc;
void setup() {
  matrix_begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}