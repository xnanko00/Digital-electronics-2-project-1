/***********************************************************************
 * 
 * Use Analog-to-digital conversion to read push buttons on LCD keypad
 * shield and display it on LCD screen.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions

#define CLK 2
#define DT 3

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and start ADC conversion every 100 ms.
 *           When AD conversion ends, send converted value to LCD screen.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize display
    lcd_init(LCD_DISP_ON);

    // create character
    uint8_t customChar[8] = {
    0b01110, 0b01111, 0b11001, 0b11111, 0b11110, 0b01110, 0b01110, 0b01010
    };


    DDRB &= ~(1<<CLK);
    PORTB  &= ~(1<<CLK);
    DDRB &= ~(1<<DT);
    PORTB  &= ~(1<<DT);
   

    lcd_command(1<<LCD_CGRAM);       // Set addressing to CGRAM (Character Generator RAM)
                                     // ie to individual lines of character patterns
    for (uint8_t i = 0; i < 8; i++)  // Copy new character patterns line by line to CGRAM
        lcd_data(customChar[i]);
    lcd_command(1<<LCD_DDRAM);       // Set addressing back to DDRAM (Display Data RAM)
                                     // ie to character codes
      // Display symbol with Character code 0

    lcd_gotoxy(1, 0); lcd_puts("value:");
    lcd_gotoxy(3, 1); lcd_puts("key:");
    lcd_gotoxy(8, 0); lcd_puts("a");  // Put ADC value in decimal
    lcd_gotoxy(13,0); lcd_puts("b");  // Put ADC value in hexadecimal
    lcd_gotoxy(8, 1); lcd_puts("c");  // Put button name here

    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"

    ADMUX |= (1<<REFS0);
    ADMUX &= ~(1<<REFS1);

    // Select input channel ADC0 (voltage divider pin)

    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0)); //ADC0
//  ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1));  ADMUX |= (1<<MUX0); //ADC1
//  ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX0));  ADMUX |= (1<<MUX1); //ADC2

    // Enable ADC module

    ADCSRA |= (1<<ADEN);

    // Enable conversion complete interrupt

    ADCSRA |= (1<<ADIE);

    // Set clock prescaler to 128

    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 33 ms and enable overflow interrupt

    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Use single conversion mode and start conversion every 100 ms.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static uint8_t no_of_overflows = 0;
    no_of_overflows++;
    if (no_of_overflows >= 3)
    {
        ADCSRA |= (1<<ADSC);
        // Do this every 3 x 33 ms = 100 ms
        if (no_of_overflows >= 6){}
        no_of_overflows = 0;
    }
}

/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display converted value on LCD screen.
 **********************************************************************/
ISR(ADC_vect)
{
    uint8_t clk, dt;
    uint16_t x_value, y_value;
    uint16_t up, down, left, right;
    static short x_move = 0;
    static short y_move = 0;
    static uint8_t move = 0;
    char string[4];  // String for converted numbers by itoa()

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    // Convert "value" to "string" and display it
    ADCSRA |= (1<<ADSC);
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
    x_value = ADC;
    itoa(x_value, string, 10);
    lcd_gotoxy(8, 0);
    lcd_puts("    ");
    lcd_gotoxy(8, 0);
    lcd_puts(string);

    up = down = left = right = 0;

    ADCSRA |= (1<<ADSC);
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1));  ADMUX |= (1<<MUX0); //ADC1
    y_value = ADC;

    itoa(y_value, string, 10);
    lcd_gotoxy(13,0);
    lcd_puts("    ");
    lcd_gotoxy(13,0);
    lcd_puts(string);

    if(y_value <= 100)
      right = 1;
    if (x_value <= 100)
      up = 1;
    if (x_value >= 1000)
      down = 1;
    if (y_value >= 1000)
       left = 1;
    

    move++;
    if (move >= 10)
    {
      lcd_gotoxy(x_move, y_move);
      lcd_puts(" ");
      y_move = y_move - up + down;
      x_move = x_move + right - left;
      move = 0;
      if (y_move > 1)
        y_move = 1;
      if (y_move < 0)
        y_move = 0;
      if (x_move > 15)
        x_move = 0;
      if (x_move < 0)
        x_move = 15;

      clk = (PINB & (1<<CLK))>>CLK;
      dt = (PINB & (1<<DT))>>DT;
      itoa(clk, string, 10);
      lcd_gotoxy(8, 1);
      lcd_puts(string);
      lcd_puts(" ");
      itoa(dt, string, 10);
      lcd_puts(string);
      lcd_puts(" ");
    }
    
    lcd_gotoxy(x_move, y_move);
    lcd_putc(0x00);
          
}