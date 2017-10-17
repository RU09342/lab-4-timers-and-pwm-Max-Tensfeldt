Software PWM
Max Tensfeldt
Intro to Embedded - Section 2

PWM is pulse width modulation and is used for the following section as the ability to dim a light. The goal of this lab was to change the state of an LED between ten steps of brightness. In order to do this, there are two main methods, through software or hardware. For this section of the lab, it is implemented via software meaning that there will be no use of the PWM OUTMOD7 (reset/set). Instead, software is used to mimic the process of moving from button pressed states. The process of debouncing was used in this section as well as the last. The only main addition is the use of a for loop to run the LED at the correct PWM state.

Just like the prior section, the interrupt is used when a button is pressed and timer is used for debounce. A timer is implemented to run the debouncer time and PWM time. The interrupt code block is used to move from duty cycle to duty cycle after every button press. This duty cycle is used in the for loop to control the RED LED which was the dedicated PWM LED; on the other hand, the GREEN LED was lit up when the button was pressed to indicate a PWM duty cycle shift. The duty cycle operated in ten steps of brightness with 0% being the lowest and 100% being the highest. When the button was pressed, the duty cycle increased by 10% until 100% was hit, after that it reset back to 0%. The code description applies to every board as they each ran under the same implementation.

* MSP430G2553
LED = P1.0 and P1.6
Button = P1.3 

* MSP430FR6989
LED = P1.0 and P9.7
Button = P1.1

* MSP430FR2311
LEDs = P1.0 and P2.0
Button = P1.1

* MSP430FR5994
LEDs used were P1.0 and P1.1
Button = P5.5

* MSP430F5529
LED = P1.0 and P4.7
Button = P1.1
