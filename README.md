# pantry_light_timer
LED light strip timer using ATTiny13, triggered by PIR and LDR.

## Description:

The inside of the pantry doorway is trimmed with an inexpensive 12V LED strip light, like this one:
https://www.amazon.com/Indoor-Warm-White-Strip-Light/dp/B0BBD6B7DP

An ATTiny13a controls an IRL540N power MOSFET, which turns the light strip on and off. PWM is used to fade the lights in and out.

A photoresistor (light dependent resistor) and a PIR sensor are used to wake the device.

I used a Mini360 DC-DC HM Buck Converter Step Down Power Supply Module to provide a 5V supply to the ATTiny and sensors.

## Simulation:
https://www.tinkercad.com/things/asS1emhaEzA-led-strip-light-timer-pir-and-ldr-triggers

## Next Steps:
* Use interrupts instead of a loop to read the triggers.
* 3D print a case
