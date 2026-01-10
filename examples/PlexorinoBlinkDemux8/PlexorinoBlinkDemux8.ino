// PlexorinoBlinkDemux8.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoBlinkDemux8
  -------------------
  Simple sanity-check example for the demultiplexer only.

  Hardware:
    - Demux: one 74HC259 (8 outputs)

  Behaviour:
    - Turns ALL outputs ON
    - Turns ALL outputs OFF
    - Repeats

  Notes:
    - Uses PlexorinoDemux only (no mux)
    - Demonstrates writeBits() for bulk updates
    - Address lines are driven only during each write and released to high-Z
*/

PlexorinoDemux demux(PlexWidth::W8);

void setup() {
  demux.begin();
  demux.reset();   // ensure known state
}

void loop() {
  demux.writeBits(0xFF);  // all 8 outputs HIGH
  delay(300);

  demux.writeBits(0x00);  // all 8 outputs LOW
  delay(300);
}
