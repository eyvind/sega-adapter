# Sega Megadrive controller to Atari 8-bit adapter

Adapt a Sega Megadrive (Genesis) controller to the 9-pin Atari joystick
standard using a Microchip PIC 16F1847 microcontroller.


## Features

The B button on the Megadrive controller is converted to the normal
joystick button.  Buttons A and C are connected to pins 5 and 9,
respectively; these can be read as second and third joystick buttons by
the computer.

The Start button is mapped to joystick button 1.

### "A is up" toggle

Holding the Start button down for a second switches the A button to "up"
to allow it to be used as a jump button in up-to-jump games.  Holding
Start again switches the mapping back.

### Autodetection

The adapter does not map the second and third joystick buttons unless a
Megadrive controller is detected.  This allows the computer to detect the
presence of a multibutton controller.


## Compatibility
### Atari 8-bit computers

Games following the [Joy2B](https://github.com/ascrnet/Joy2Bplus)
standard can be played using this adapter.

### Sega controllers

The program is theoretically compatible with a six-button Megadrive
controller, but this has not been tested.  The extra X, Y, Z, and Mode
buttons are not mapped to anything even if a six-button controller is
used.

Sega Master System controllers are also theoretically supported.


## Build

`xc8 --chip=16f1847 sega-adapter.c`


## Program

TODO


## Pinout

```
                      PIC 16F1847
                     +---------_---------+
                     |                   |
            Atari 6 -|  1  RA2   RA1  18 |- Atari 1
                     |                   |
             SEGA 7 -|  2  RA3   RA0  17 |- Atari 2
                     |                   |
                  X -|  3  RA4   RA7  16 |- Atari 3
                     |                   |
                  X -|  4  RA5   RA6  15 |- Atari 4
                     |                   |
    Atari 8  SEGA 8 -|  5  GND   +5v  14 |- Atari 7  SEGA 5
                     |                   |
             SEGA 1 -|  6  RB0   RB7  13 |- Atari 5
                     |                   |
             SEGA 2 -|  7  RB1   RB6  12 |- Atari 9
                     |                   |
             SEGA 3 -|  8  RB2   RB5  11 |- SEGA 9
                     |                   |
             SEGA 4 -|  9  RB3   RB4  10 |- SEGA 6
                     |                   |
                     +-------------------+
```
