# Timelapse
Energia program for making timelapses with a DSLR

## Use
Use a TM4C123GXL board. Others might need pin changes for buttons/leds.
SW1 starts an (effectivly) indefinite timelapse capture. By default a picture
will be taken every 2 seconds. SW2 starts an indefinite bulb exposure. 
Pressing SW2 again will end the exposure. The camera must be in bulb mode (or
equivalent).

## Pins
| Nikon pin | TI pin |
| --------- | ------ |
| 9         | C4     |
| 4         | C5     |
| 6 (gnd)   | gnd    |

Here is a pinmap for a camera you probably don't have.

![pin map](https://github.com/dylan-wright/camera-control/raw/master/nikon_10pins.gif "Pin map for Nikon D100")
