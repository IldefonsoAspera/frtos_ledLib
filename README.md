# frtos_ledLib
Manager of LED's patterns, for STM32 and FreeRTOS

Objectives of this project:

* Thread that manages LED patterns and can switch between low and high priority patterns.
* Capable of managing N LEDs.
* SW implementation with a list of patterns and callbacks to manage each LED.
* Minimal processing time needed for starting/stopping a LED pattern, main processing must occur in thread.
