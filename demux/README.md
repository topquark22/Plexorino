# Plexorino/demux

Skeleton code for using the 74HC259 addressable latch with Arduino. This increases the number of digital outputs.

## Configurations

* **16 outputs:** At the expense of taking up 6 Arduino pins, with the use of two 74HC259 chips, 16 output lines are available.
  
* **8 outputs:** Pin A2 is assigned to control the second 74HC259 (if present.) If you only need 8 outputs, then comment out `#define USE_BANK2` at the top of `demux.ino`. This frees up A2 to be used for something else.

## Wiring

Note that we left all of the SPI and I2C pins free.

**Arduino:**

| pin | description           | 74HC259 pin |
|-----|-----------------------|-------------|
| D2  | address bus 0         | 1           |
| D3  | address bus 1         | 2           |
| D4  | address bus 2         | 3           |
| D8  | data to latch         | 13          |
| A3  | latch enable (chip 1) | 14 (chip 1) |
| A2  | latch enable (chip 2) | 14 (chip 2) |

**74HC259:**

- custom: To your circuit

| pin | Chip | description      | wiring  |
|-----|------|------------------|---------|
| 1   | both | address bus 0    | D2      |
| 2   | both | address bus 1    | D3      |
| 3   | both | address bus 2    | D4      |
| 4   | 1,2  | line 0,8 output  | custom  |
| 5   | 1,2  | line 1,9 output  | custom  |
| 6   | 1,2  | line 2,10 output | custom  |
| 7   | 1,2  | line 3,11 output | custom  |
| 8   | both | Vss              | GND     |
| 9   | 1,2  | line 4,12 output | custom  |
| 10  | 1,2  | line 5,13 output | custom  |
| 11  | 1,2  | line 6,14 output | custom  |
| 12  | 1,2  | line 7,15 output | custom  |
| 13  | both | data to latch    | D8      |
| 14  | 1    | latch enable     | A3      |
| 14  | 2    | latch enable     | A2      |
| 15  | both | master reset     | +5V \[1] |
| 16  | both | Vdd              | +5V     |

\[1] You can implement master reset in your circuit, but this sketch does not use it.
