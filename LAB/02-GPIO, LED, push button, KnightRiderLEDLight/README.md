## Synchronize git

Use [git commands](https://github.com/tomas-fryza/Digital-electronics-2/wiki/Git-useful-commands) to add, commit, and push all local changes to your remote repository. Check the repository at GitHub web page for changes.


## Experiments on your own

1. Connect five LEDs and a push button to the microcontroller, modify `02-leds` code, and program an application that will--after you press the button--ensure that only one of LED is switched on at a time in [Knight Rider style](https://www.youtube.com/watch?v=w-P-2LdS6zk).

2. Simulate the Knight Rider application in SimulIDE.

Extra. Program the [PWM generator](https://www.analogictips.com/pulse-width-modulation-pwm/) using the delay library. Let the duty cycle of the PWM signal be changed continuously and the signal is connected to one of the LEDs. How does a change of duty cycle affect the brightness of an LED?


## Lab assignment

1. LED example. Submit:
    * Tables for DDRB, PORTB, and their combination,
    * Table with input/output pins available on ATmega328P,
    * C code with two LEDs and a push button,
    * Screenshot of SimulIDE circuit.

2. Knight Rider application. Submit:
    * C code.

The deadline for submitting the task is the day before the next laboratory exercise. Use [BUT e-learning](https://moodle.vutbr.cz/) web page and submit a single PDF file.
