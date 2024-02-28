# Multiplexorino

Skeleton code for using the 74HC259 addressable latch with Arduino. This increases the number of digital outputs:

## 16 outputs

At the expense of 6 output pins on the Arduino, 16 output pins are available with the use of two 74HC259 chips.

## 8 outputs

Pin A2 is assigned to control the second 74HC259 (if present.) If you only need 8 outputs, then comment out the line `#define USE_BANK2` at the top of `multiplex.ino`. This frees up A2 to be used for something else.

## Wiring

Note that we left free all of the PWM-capable, SPI and I2C pins.

**Arduino:**

| pin | description           | 74HC259 pin |
|-----|-----------------------|-------------|
| D2  | line address, 1's bit | 1           |
| D4  | line address, 2's bit | 2           |
| D7  | line address, 4's bit | 3           |
| D8  | data                  | 13          |
| A3  | latch enable (chip 1) | 14 (chip 1) |
| A2  | latch enable (chip 2) | 14 (chip 2) |

**74HC259:**

| pin | Chip | description            | wiring  |
|-----|------|------------------------|---------|
| 1   | both | line address, 1's bit  | D2      |
| 2   | both | line address, 2's bit  | D4      |
| 3   | both | line address, 4's bit  | D7      |
| 4   | 1,2  | line 0,8 output        | custom  |
| 5   | 1,2  | line 1,9 output        | custom  |
| 6   | 1,2  | line 2,10 output       | custom  |
| 7   | 1,2  | line 3,11 output       | custom  |
| 8   | both | Vss                    | GND     |
| 9   | 1,2  | line 4,12 output       | custom  |
| 10  | 1,2  | line 5,13 output       | custom  |
| 11  | 1,2  | line 6,14 output       | custom  |
| 12  | 1,2  | line 7,15 output       | custom  |
| 13  | both | data input             | D8      |
| 14  | 1    | latch enable           | A3      |
| 14  | 2    | latch enable           | A2      |
| 15  | both | master reset           | +5V \[1] |
| 16  | both | Vdd                    | +5V     |

\[1] You can implement master reset in your own circuit, but this sketch does not use it.
