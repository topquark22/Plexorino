# Plexorino/mux8

8-line multiplexer for input to Arduino.

## 74LS151 pinout

- **E\***: Demultiplexed input signals
- custom: Your circuit

| pin | function | wire to |
|-----|----------|---------|
| 1   | E3  | custom |
| 2   | E2  | custom |
| 3   | E1  | custom |
| 4   | E0  | custom |
| 5   | multiplexed signal  | A0 |
| 6   | multiplexed signal (inverted)  |  |
| 7   | strobe  | GND \[1\] |
| 8   | Vss  | GND |
| 9 | addr 4's bit | D4 |
| 10 | addr 2's bit | D3 |
| 11 | addr 1's bit | D2 |
| 12 | E7 | custom |
| 13 | E6 | custom | 
| 14 | E5 | custom | 
| 15 | E4 | custom |
| 16 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but this sketch does not use it.
