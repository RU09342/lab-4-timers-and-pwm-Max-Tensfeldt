Debouncing
Max Tensfeldt
Intro to Embedded - Section 2

Prior to this lab, debouncing was done in a sloppy manner. Bouncing occurs when a button is pressed and following the release, the signal reverberates in a way and falls to zero similar to a dampening wave. In labs two and three, anytime a button was pressed, a loop followed that would delay the whole process for the short amount of time it took for a button to zero out. In this section of lab 4, debouncing was completed without delaying the processor with a loop, but with an interrupt and timer. Whenever a button was pressed, it would trigger a interrupt that used a timer to cut away the button’s input for the short duration of bouncing. The button input was then enabled again after the delay. This is different than the prior method because the processor is not being delayed, the button input is being turned off and on while the processor runs.
To test the functionality of this program, a button and two LEDs were implemented. When the button is pressed, the RED LED blinks with the GREEN LED representing the current state of the interrupt. Below are all of the pins used for each board with each board being implemented the same.

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
