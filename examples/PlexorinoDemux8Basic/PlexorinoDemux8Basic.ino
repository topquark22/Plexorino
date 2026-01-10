// PlexorinoDemux8Basic.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoDemux8Basic
  -------------------
  Basic example showing how to control individual demux outputs.

  Hardware:
    - Demux: one 74HC259 (8 outputs)

  Behaviour:
    - Sequentially turns each output ON, then OFF

  Notes:
    - Uses PlexorinoDemux only
    - Explicit begin()
    - Uses muxAddr_t for address variables
*/

PlexorinoDemux demux(PlexWidth::W8);

void setup() {
  demux.begin();
  demux.reset();   // start from a known state
}

void loop() {
  for (muxAddr_t i = 0; i < demux.count(); i++) {
    demux.write(i, true);
    delay(200);
    demux.write(i, false);
  }
}
