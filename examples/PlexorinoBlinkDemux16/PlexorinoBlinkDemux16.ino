// PlexorinoBlinkDemux16.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoBlinkDemux16
  --------------------
  Simple sanity-check example for the 16-bit demultiplexer.

  Hardware:
    - Demux: two 74HC259 chips (16 outputs total)

  Behaviour:
    - Turns ALL 16 outputs ON
    - Turns ALL 16 outputs OFF
    - Repeats

  Notes:
    - Uses PlexorinoDemux only (no mux)
    - Demonstrates writeBits() with a 16-bit pattern
    - Address lines are driven only during each write and released to high-Z
*/

PlexorinoDemux demux(PlexWidth::W16);

void setup() {
  demux.begin();
  demux.reset();   // ensure known state
}

void loop() {
  demux.writeBits(0xFFFF);  // all 16 outputs HIGH
  delay(300);

  demux.writeBits(0x0000);  // all 16 outputs LOW
  delay(300);
}
