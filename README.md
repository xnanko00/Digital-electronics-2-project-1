# Project 1


### Team members

* Matej Nanko 220823 (responsible for documentation and code)
* Jan Gross 230067 (responsible for github and code)

## Hardware description

Rotary encoder information is in a format of two digital signals for rotation and a digital button, analog joy-stick can be understood as two potentiometers that need to be connected to analog inputs and a digital button. LCD has digital pin connections.

<img src="https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/images/schematic1.png" width=60% height=60%>

## Software description

`src` [main](https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/src/main.c)

`lib` 
[gpio.h](https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/lib/gpio/gpio.h)
[lcd.h](https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/lib/lcd/lcd.h)
[timer.h](https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/include/timer.h)


<img src="https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/images/flowchart1.png" width=70% height=70%>

## Video

[Practical implementation example](https://youtube.com/shorts/cnpW_S2geDI?feature=share)

## References

1. https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
2. https://res.cloudinary.com/iwh/image/upload/q_auto,g_center/assets/1/26/Digilent_PmodCLP_-_Reference_Manual.pdf
3. https://arduino.stackexchange.com/questions/49315/using-different-adc-channels
4. https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
