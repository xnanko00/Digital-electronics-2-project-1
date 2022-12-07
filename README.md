# Project 1

Application of analog joy-stick (2 ADC channels, 1 push button), rotary encoder, and Digilent PmodCLP LCD module.

## Instructions

The goal of the project is cooperation in pairs, further study of the topic, design of own solutions, implementation, creation of project documentation and presentation of results. The division of roles and tasks within the team is up to their members.

* Students work on a project in the labs during the 10th and 11th weeks of the semester.

* Through the BUT e-learning, students submit a link to the GitHub repository, which contains the complete project in PlatfomIO and a descriptive README file. The submission deadline is the day before the next laboratory, i.e. in 2 weeks.

* The source code for the AVR must be written in C and/or Assembly and must be implementable on Arduino Uno board using toolchains from the semester, ie PlatformIO and not in the Arduino-style. No other development tools are allowed.



### Team members

* Matej Nanko 220823 (responsible for documentation and code)
* Jan Gross 230067 (responsible for github and code)

## Hardware description

Rotary encoder information is in a format of two digital signals for rotation and a digital button, analog joy-stick can be understood as two potentiometers and a digital button.

<img src="https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/images/schematic1.png" width=60% height=60%>

## Software description

Put flowchats of your algorithm(s). Write descriptive text of your libraries and source files. Put direct links to these files in `src` or `lib` folders.
<img src="https://github.com/xnanko00/Digital-electronics-2-project-1/blob/main/lab-project-1/images/flowchart1.png" width=70% height=70%>

## References

1. https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
2. https://res.cloudinary.com/iwh/image/upload/q_auto,g_center/assets/1/26/Digilent_PmodCLP_-_Reference_Manual.pdf
3. https://arduino.stackexchange.com/questions/49315/using-different-adc-channels
4. https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
