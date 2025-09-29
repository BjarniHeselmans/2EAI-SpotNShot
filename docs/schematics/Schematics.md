# Schematics to connect the Raspberry Pi Pico to the DMX light

The Pico is fed by USB directly into the PC for debugging and determining where to send the spot in which direction.

The connection can be made using jumper wires or by directly soldering the wires together.

## MAX485
This component is used to convert the TTL signal from the Raspberry Pi Pico into a DMX signal.

## Connections
For this setup, we have the following connections:

| Raspberry Pi Pico  | MAX485  | DMX Connector |
| ------------------ | ------- | ------------- |
| Pin 40 (VBUS)     | VCC     |               |
| Pin 38 (GND)      | GND     | GND (Pin 3)   |
| Pin 1 (GP0, UART0 TX) | DI      |               |
| Pin 19 (GP14)     | DE      |               |
|                    | A       | Pin 2         |
|                    | B       | Pin 1         |

## Schematics 
![](https://github.com/PXLDigital/2EAI-PEN-2425-SpotNShot/blob/Robert/docs/schematics/src/schematic.png)
