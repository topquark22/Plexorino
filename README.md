# Plexorino

Plexorino is a small Arduino library for:

- **Multiplexing GPIO inputs** using:
  - **74LS151** (8-input mux), or
  - **74LS150** (16-input mux)
- **Demultiplexing GPIO outputs** using:
  - **74HC259** (8-bit addressable latch)
  - and optionally a second 74HC259 for 16 outputs

This library intentionally uses a **fixed, hardcoded pinout** (by design).

## Documentation

For deeper detail, see:

- [Demux details](README_demux.md)
- [Mux 8-bit mode (74LS151)](README_mux8.md)
- [Mux 16-bit mode (74LS150)](README_mux16.md)

---

## Key idea: runtime width selection (no compiler flags)

Earlier versions used compile-time defines to choose 8 vs 16. Those are gone.

Now you choose **at runtime**:

```cpp
#include <Plexorino.h>

void setup() {
  beginMux(PlexWidth::W8);       // or W16
  beginDemux(PlexWidth::W16);    // or W8
}
