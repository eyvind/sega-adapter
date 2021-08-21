# Compact adapter

The compact variant of the adapter is the recommended one to build.
DigiKey part numbers are provided as a convenience, but alternative
parts can certainly be used.


## BOM

| Component | DigiKey part number |
| --- | --- |
| PIC 16F1874 microcontroller | PIC16F1847-I/P-ND |
| 0.1uF capacitor | 1109PHCT-ND |
| 18-pin socket | ED3018-ND |
| D-sub male socket | A32088-ND |
| IDC header | S2011EC-05-ND |
| D-sub female plug with ribbon cable | H7FXH-0906G-ND |
| IDC connector | LKR10H-ND |
| Jumper header (optional) | S2011EC-01-ND |
| Jumper (optional) | S9001-ND |


### Optional jumper

The jumper is used to switch the adapter between Atari and C64 mode.  If
the adapter is only going to be used with one kind of computer, the
jumper and its header can either be omitted entirely (Atari/Amiga) or
replaced with a solder bridge or wire (C64/VIC-20).


### Optional joystick pigtail

Instead of using the IDC header and ribbon cable, a joystick pigtail can
be soldered directly to the board.  A cable from an old joystick or one
end of a joystick extension cable can be used for a pigtail; just make
sure that it has nine wires.


## Assembly notes

- The ribbon cable is 2m long, so it is a good idea to cut it to a more
  reasonable length.  The remaining cable can be used with standalone
  d-sub connectors (part number HHFP09H-ND) to make more adapters.

- When attaching the IDC connector to the ribbon cable, make sure that
  pin 1 (the red wire) is flush against the side and that there is a
  small gap on the other side.  This is because the connector has ten
  pins while the cable only has nine.

- Make sure that pin 1 of the cable is on the same side as pin 1 of the
  header when connecting the cable to the board.  Pin 1 is the one with
  the square pad on the circuit board.

- If you are using alternative parts, please note that there isn't much
  clearance between the IC socket and the IDC header.  Depending on the
  socket used, a shrouded IDC header may not fit.
