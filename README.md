# Timelapse
Energia program for making timelapses with a DSLR

## Use
Use a TM4C123GXL board. Others might need pin changes for buttons/leds.
SW1 starts an (effectivly) indefinite timelapse capture. By default a picture
will be taken every 2 seconds. SW2 starts an indefinite bulb exposure. 

### Timelapse
After pressing SW1, the timelapse exposure has to be configured. Press SW2
at this point to start a default exposure. Pressing SW1 will change the length
of time between exposures. There are 3 time settings: Default, 2 time default,
and 3 times default. Pressing SW1 will cycle through these settings. The
brighter the red led the longer the exposure gap.

### Bulb
After pressign SW2, the bulb exposure will begin. Pressing SW2 will end
the exposure. There is not configuration at the moment for this exposure.

## Pins
| Nikon pin | TI pin |
| --------- | ------ |
| 9         | C4     |
| 4         | C5     |
| 6 (gnd)   | gnd    |

Here is a pinmap for a camera you probably don't have.

![pin map](https://github.com/dylan-wright/camera-control/raw/master/nikon_10pins.gif "Pin map for Nikon D100")
