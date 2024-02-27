# 74HC259

Skeleton code for using the 74HC259 addressable latch with Arduino. This provides you with additional output lines as needed by your application.

## configuration options

### 8 output lines

At the expense of 5 output pins on the Arduino, it provides 8 output pins on one 74HC259.

Comment out the line `#define USE_BANK2` at the top of the file.

This frees up A2 for other uses.

### 16 output lines

At the expense of 6 output pins on the Arduino, it provides 16 output pins on two 74HC259.

Leave the line `#define USE_BANK2` uncommented.

## Wiring

Note we do not use any of the PWM, SPI or I2C pins, so those are free for your application.

**Arduino:**

| pin | description                  | 74HC259 pin |
|-----|------------------------------|-------------|
| D2  | output line address, 1's bit | 1           |
| D4  | output line address, 2's bit | 2           |
| D7  | output line address, 4's bit | 3           |
| D8  | data                         | 13          |
| A3  | Latch enable (chip 1)        | 14 (chip 1) |
| A2  | Latch enable (chip 2)        | 14 (chip 2) |

**74HC259:**

| pin | Chip | description                   | wiring |
|-----|------|-------------------------------|--------|
| 1   | both | output line address, 1's bit  | D2     |
| 2   | both | output line address, 2's bit  | D4     |
| 3   | both |output line address, 4's bit   | D7     |
| 4   | 1,2  | Line 0,8 output               | custom |
| 5   | 1,2  | Line 1,9 output               | custom |
| 6   | 1,2  | Line 2,10 output              | custom |
| 7   | 1,2  | Line 3,11 output              | custom |
| 8   | both | Vss                           | GND    |
| 9   | 1,2  | Line 4,12 output              | custom |
| 10  | 1,2  | Line 5,13 output              | custom |
| 11  | 1,2  | Line 6,14 output              | custom |
| 12  | 1,2  | Line 7,15 output              | custom |
| 13  | both | data input                    | D8     |
| 14  | 1    | Latch enable                  | A3     |
| 14  | 2    | Latch enable                  | A2     |
| 15  | both | Master reset (note 1)         | +5V    |
| 16  | both | Vdd                           | +5V    |

Note 1: You can implement master reset in your own code, but this sketch does not use it.
