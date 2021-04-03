#include <Arduino.h>
#include <RTClib.h>
#include "gpio.h"
#include <SPI.h>
#include "matrix.h"
#define F_CPU 16000000L
RTC_DS3231 my_rtc;
volatile enum {NONE,UP,DOWN,SELECT} interrupt_event;
void button_interrupt_handle();
void print_time(DateTime &time);  
void setup() {
  matrix_begin();
  Serial.begin(115200);
  if(!my_rtc.begin()){
    Serial.println("RTC init fail");
    while(1); // infinity loop here since it's critical error
  }
  interrupt_event = NONE;
  pinMode(BUTTON_SELECT_PIN,INPUT_PULLUP);
  pinMode(BUTTON_UP_PIN,INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN,INPUT_PULLUP);
  attachInterrupt(0,button_interrupt_handle,FALLING);
}

void loop() {
  DateTime now =my_rtc.now();
  print_time(now);
  switch(interrupt_event){
    case NONE:
      _delay_ms(200);
      break;
    case UP:
    case DOWN:
      // at the main screen up and down button has no effect
      break;
    case SELECT:
      //setting_time();
      break;
  }
  interrupt_event=NONE;
}
void print_time(DateTime &time){
  matrix_print_char(0,0,time.hour()/10);
  matrix_print_char(8,0,time.hour()%10);
}
void button_interrupt_handle(){
  if(interrupt_event!=NONE) return;
  if(digitalRead(BUTTON_DOWN_PIN)==0){
    interrupt_event=DOWN;
    return;
  }
  if(digitalRead(BUTTON_DOWN_PIN)==0){
    interrupt_event=UP;
    return;
  }
  interrupt_event=SELECT;
}