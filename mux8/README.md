# Plexorino/mux8

8-line multiplexer for input to Arduino.

*Note: Output wiring has changed on this branch. In the library we use the inverted muxer output on pin 6, instead of the straight output on pin 5 as before. This is for code consistency with the 16-bit case with the 74LS150.*

## 74LS151 pinout and wiring

- **En**: Input signal at address n
- custom: From your circuit

| pin | function | wire to |
|-----|----------|---------|
| 1   | E3       | custom  |
| 2   | E2       | custom  |
| 3   | E1       | custom  |
| 4   | E0       | custom  |
| 5   | multiplexed signal  | A0 |
| 6   | multiplexed signal (inverted) |  |
| 7   | STROBE | GND \[1\] |
| 8   | Vss     | GND |
| 9 | address bus 2 | D4 |
| 10 | address bus 1 | D3 |
| 11 | address bus 0 | D2 |
| 12 | E7 | custom |
| 13 | E6 | custom | 
| 14 | E5 | custom | 
| 15 | E4 | custom |
| 16 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but stock Plexorino does not use it.
