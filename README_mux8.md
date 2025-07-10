# Plexorino/mux8

8-line multiplexer for input to Arduino.

## 8-bit vs. 16-but mux

If your use case is 8-input (74LS151) only and you need to use pin A1 for something else, then define `MUX8_ONLY` at compile time. But in any case, it will still work; you just won't be able to use pin A1 for anything else because it will be dedicated to address line 3 for the 74LS150 (MUX16) use case.

## 74LS151 pinout and wiring

*Note: Output wiring has changed in 2.x. We now use the inverted 74LS151 output on pin 6, instead of the straight output on pin 5 as before. This is for code consistency with the 16-bit case with the 74LS150.*

- **En**: Input signal at mux address n.  Include external pullup resistors if required.
- custom: From your circuit, according to your use case.

| 74LS151 pin | description | wire to |
|-----|-------|------------|
| 1   | input E3      | custom  |
| 2   | input E2       | custom  |
| 3   | input E1       | custom  |
| 4   | input E0       | custom  |
| 5   | multiplexed output | |
| 6   | multiplexed output (inverted) | Arduino A0 |
| 7   | input STROBE | GND \[1\] |
| 8   | Vss     | GND |
| 9 | address bus 2 | Arduino D4 |
| 10 | address bus 1 | Arduino D3 |
| 11 | address bus 0 | Arduino D2 |
| 12 | input E7 | custom |
| 13 | input E6 | custom | 
| 14 | input E5 | custom | 
| 15 | input E4 | custom |
| 16 | Vdd | +5V |

 \[1\] You can implement STROBE in your circuit, but stock Plexorino does not use it.
