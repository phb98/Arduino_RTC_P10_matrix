#include "matrix.h"
#include "gpio.h"
#include <Arduino.h>
#include "font.h"
#include <SPI.h>
uint32_t matrix_buffer[32];
void matrix_power_off(){

}
void matrix_power_on(){

}
/*call this function periodically*/
void matrix_IRQ_call(){
    static uint8_t row;
    uint8_t temp=0;
    matrix_power_off(); // turn off matrix when sending data
    matrix_set_row(row);
    digitalWrite(MATRIX_CS_PIN,0);// told matrix to accept new data 
    /*send data to first matrix*/
    for(int j=3;j>=0;j--){
        for(int i=0;i<4;i++){
            temp=(matrix_buffer[i*4+row]>>(j*8));
            SPI.transfer(temp);
        }
    }
    /*send data to second matrix*/
    for(int j=3;j>=0;j--){
        for(int i=0;i<4;i++){
            temp=(matrix_buffer[i*4 + 16 + row]>>(j*8)); // second matrix begin from row 16
            SPI.transfer(temp);
        }
    }
    digitalWrite(MATRIX_CS_PIN,1); // stop sending data
    matrix_power_on();
    if(row>=3) row=0;
    else row++;
}
void matirx_print_char(uint8_t x, uint8_t y, uint8_t ch){
    uint32_t temp=0;
    if(x>31 || y>31) return;
    for(int i=0;i<8;i++){
        if(i+y>31) continue;
        matrix_buffer[i+y] &= ~((uint32_t)0xff<<x);
        temp=pgm_read_byte( &(font8x8_ib8x8u[ch][i]) );
        temp<<=x;
        matrix_buffer[i+y]|=temp;
    }
}
