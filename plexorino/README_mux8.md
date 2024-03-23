# Plexorino/mux8

8-line multiplexer for input to Arduino.

Comment out `#define MUX16` in `plexorino.h`.

## 74LS151 pinout and wiring

*Note: Output wiring has changed on this branch. In the library we use the inverted 74LS151 output on pin 6, instead of the straight output on pin 5 as before. This is for code consistency with the 16-bit case with the 74LS150.*

- **En**: Input signal at mux address n
- custom: From your circuit, according to your use case

| 74LS151 pin | mode | description | wire to |
|-----|-------|---|---------|
| 1   | input | E3       | custom  |
| 2   | input | E2       | custom  |
| 3   | input | E1       | custom  |
| 4   | input | E0       | custom  |
| 5   | output | multiplexed signal  | |
| 6   | output | multiplexed signal (inverted) | Arduino A0 |
| 7   | input | STROBE | GND \[1\] |
| 8   | power | Vss     | GND |
| 9 | input | address bus 2 | Arduino D4 |
| 10 | input | address bus 1 | Arduino D3 |
| 11 | input | address bus 0 | Arduino D2 |
| 12 | input | E7 | custom |
| 13 | input | E6 | custom | 
| 14 | input | E5 | custom | 
| 15 | input | E4 | custom |
| 16 | power | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but stock Plexorino does not use it.
