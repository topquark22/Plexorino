# Plexorino/mux8

8-line multiplexer for input to Arduino.

## 74LS151 pinout

**D\***: input signals

| pin | function | wire to |
|-----|----------|---------|
| 1   | D3  | custom |
| 2   | D2  | custom |
| 3   | D1  | custom |
| 4   | D0  | custom |
| 5   | multiplexed signal  | A0 |
| 6   | multiplexed signal (inverted)  |  |
| 7   | strobe  | GND [1] |
| 8   | Vss  | GND |
| 9 | addr 4's bit | D8 |
| 10 | addr 2's bit | D7 |
| 11 | addr 1's bit | D6 |
| 12 | D7 | custom |
| 13 | D6 | custom | 
| 14 | D5 | custom | 
| 15 | D4 | custom |
| 16 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but this sketch does not use it.
