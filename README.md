# Plexorino

With additional hardware, we can expand the number of digital input/output pins on the Arduino, beyond the bare GPIO provided.

Plexorino brings you skeleton code for multiplexer and demultiplexer to achieve this. Take this logic and use it in your own circuit project.

A design goal was to minimize the number of GPIO pins used. In particular:

- We have left pins 9-13 free, which are used by SPI.
- We have left pins A4, A5 free, which are used by I2C.
- We have left pins 5, 6, 7 free, of which 5 and 6 are PWM-capable.

| module          | use case                | I.C. used  | GPIO pins used     |
|-----------------|-------------------------|------------|--------------------|
| [demux](/demux) | 8-output demultiplexer  | 74HC259    | 2, 3, 4, 8, A3     |
| [demux](/demux) | 16-output demultiplexer | 74HC259 x2 | 2, 3, 4, 8, A3, A2 |
| [mux8](/mux8)   | 8-to-1 multiplexer      | 74LS151    | 2, 3, 4, A0        |
| [mux16](/mux16) | 16-to-1 multiplexer     | 74LS150    | 2, 3, 4, A0, A1    |

If you like this, please sponsor my Patreon by hitting the Sponsorship button. Thank you!
