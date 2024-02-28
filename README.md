# Plexorino

Skeleton code for multiplexer and demultiplexer for Arduino input/output pins.

| module          | description                        |chip used | GPIO pins used     |
|-----------------|------------------------------------|----------|--------------------|
| [demux](/demux) | 8- and 16-way output demultiplexer | 74HC259  | 2, 3, 4, 8, (A2), A3 |
| [mux8](/mux8)   | 8-to-1 input multiplexer           | 74LS151  | 2, 3, 4, A0        |
| [mux16](/mux16) | 16-to-1 input multiplexer          | 74LS150  | 2, 3, 4, A0, A1    |

Note: **demux** only uses pin A2 in 16-way configuration.
