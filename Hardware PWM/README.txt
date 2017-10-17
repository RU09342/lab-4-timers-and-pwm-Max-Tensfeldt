Hardware PWM
Max Tensfeldt
Intro to Embedded - Section 2

For this section, instead of implementing PWM with software, hardware was used. This section was very similar to the software section except for a couple differences. The first was the ability to use OUTMOD which allowed for the switch in PWM for the LED. The next was the for loop being cut from the project due to the use of OUTMOD. The code was the same in most aspects between software and hardware. What still had to remain was all the timer information and code involving the debouncing which was still needed as a button was being used again. There are easier ways to complete hardware PWM but for the sake of comparison the hardware was a close image of the software PWM implementation.
The same goes for this section as the last, when the button is pressed, the RED LED that starts at 50% duty cycle will switch up by 10% until at 100% where it will reset back to 0%. The GREEN LED is only used as a identifier for when the button is pressed to show that PWM duty cycle has changed. Below are the pins for this section.

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

