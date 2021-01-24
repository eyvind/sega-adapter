# Sega Mega Drive controller to Atari 8-bit adapter

Adapt a Sega Mega Drive (Genesis) controller to the 9-pin Atari joystick
standard using a Microchip PIC 16F1847 microcontroller.


## Features

The B button on the Mega Drive controller is mapped to the normal
joystick button.  Buttons A and C are connected to pins 5 and 9 on the
joystick port; these can be read as second and third joystick buttons by
the computer.

The Start button is mapped to joystick button 1.

### "A is up" toggle

Holding the Start button down for a second switches the A button to "up"
to allow it to be used as a jump button in up-to-jump games.  Holding
Start again switches the mapping back.

### Autodetection

The adapter does not drive the second and third joystick button outputs
unless a Mega Drive controller is detected.  This allows the computer to
detect the presence of a multibutton controller.


## Compatibility
### Atari 8-bit computers

Games following the [Joy2B+](https://github.com/ascrnet/Joy2Bplus)
standard can be played using this adapter.

### Commodore computers (experimental)

The C64, C128, and VIC-20 can also read the second and third buttons.
Games on those machines expect the signals to be active high, which is
opposite to Joy2B+/Sega.

Pulling the /C64 pin (number 4) low inverts the outputs for those
buttons to allow them to be read correctly by the 8-bit Commodores.

The Amiga follows the same convention as Atari and Sega.

### Sega controllers

The adapter is theoretically compatible with a six-button Mega Drive
controller, but this has not been tested.  The extra X, Y, Z, and Mode
buttons are not mapped to anything even if a six-button controller is
connected.

Sega Master System controllers are also theoretically supported,
including the second button.


## Build

`xc8 --chip=16f1847 sega-adapter.c`


## Program

TODO


## Pinout

```
                      PIC 16F1847
                     +---------_---------+
                     |                   |
            Atari 5 -|  1  RA2   RA1  18 |- Atari 1
                     |                   |
            Atari 6 -|  2  RA3   RA0  17 |- Atari 2
                     |                   |
            Atari 9 -|  3  RA4   RA7  16 |- Atari 3
                ___  |                   |
                C64 -|  4  RA5   RA6  15 |- Atari 4
                     |                   |
    Atari 8  SEGA 8 -|  5  GND   +5v  14 |- Atari 7  SEGA 5
                     |                   |
             SEGA 1 -|  6  RB0   RB7  13 |- SEGA 6
                     |                   |
             SEGA 2 -|  7  RB1   RB6  12 |- SEGA 7
                     |                   |
             SEGA 3 -|  8  RB2   RB5  11 |- SEGA 9
                     |                   |
             SEGA 4 -|  9  RB3   RB4  10 |- X
                     |                   |
                     +-------------------+
```

Information on reading Sega controllers came from
https://github.com/jonthysell/SegaController/wiki/How-To-Read-Sega-Controllers
