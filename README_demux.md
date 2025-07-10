# Plexorino/demux

Skeleton code for using the 74HC259 addressable latch as a demultiplexer with Arduino. This increases the number of digital outputs.

## Configurations

* **16 outputs:** At the expense of taking up 6 Arduino GPIO pins, with the use of two 74HC259 chips, 16 output lines are available.  Pin A2 is assigned to control the second 74HC259 in this case.
* **8 outputs:** If you only need 8 outputs, then you only need one 74HC259 chip. If you want to use pin A2 for something else, then define `DEMUX8_ONLY` at compile time. Otherwise, it will still work; you will just not be able to use pin A2.

## Wiring

The 74HC259 chips are 0, and 1 (if present).

**Arduino:**

| pin | description              | Chip | 74HC259 pin  |
|-----|--------------------------|------|--------------|
| D2  | address bus 0            | both | 1            |
| D3  | address bus 1            | both | 2            |
| D4  | address bus 2            | both | 3            |
| D5  | data                     | both | 13           |
| A3  | latch enable (addr 0-7)  | 0    | 14           |
| A2  | latch enable (addr 8-15) | 1    | 14           |

**74HC259:**

- custom: To your circuit, according to your use case.

| pin | Chip | description      | wiring  |
|-----|------|------------------|---------|
| 1   | both | address bus 0    | D2      |
| 2   | both | address bus 1    | D3      |
| 3   | both | address bus 2    | D4      |
| 4   | 0,1  | line 0,8 output  | custom  |
| 5   | 0,1  | line 1,9 output  | custom  |
| 6   | 0,1  | line 2,10 output | custom  |
| 7   | 0,1  | line 3,11 output | custom  |
| 8   | both | Vss              | GND     |
| 9   | 0,1  | line 4,12 output | custom  |
| 10  | 0,1 |  line 5,13 output | custom  |
| 11  | 0,1  | line 6,14 output | custom  |
| 12  | 0,1  | line 7,15 output | custom  |
| 13  | both | data             | D5      |
| 14  | 0    | latch enable     | A3      |
| 14  | 1    | latch enable     | A2      |
| 15  | both | master reset     | +5V \[1] |
| 16  | both | Vdd              | +5V     |

\[1] You can implement master reset in your circuit, but stock Plexorino does not use it.
