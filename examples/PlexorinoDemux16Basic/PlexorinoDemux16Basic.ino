// PlexorinoDemux16Basic.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoDemux16Basic
  --------------------
  Basic example showing how to control individual demux outputs (16-bit).

  Hardware:
    - Demux: two 74HC259 chips (16 outputs total)

  Behaviour:
    - Sequentially turns each output ON, then OFF

  Notes:
    - Uses PlexorinoDemux only
    - Explicit begin()
    - Uses muxAddr_t for address variables
*/

PlexorinoDemux demux(PlexWidth::W16);

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
