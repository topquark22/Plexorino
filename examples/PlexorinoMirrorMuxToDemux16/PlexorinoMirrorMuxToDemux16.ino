// PlexorinoMirrorMuxToDemux16.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoMirrorMuxToDemux16
  --------------------------
  Mirrors 16 mux inputs to 16 demux outputs.

  Hardware:
    - Mux: 74LS150 (16:1)
    - Demux: two 74HC259 chips (16 outputs total)

  Notes:
    - Uses the split classes: PlexorinoMux / PlexorinoDemux
    - Width is selected at runtime (W16 here)
    - Shared address lines are driven only during each read/write and then released to INPUT
*/

PlexorinoMux   mux(PlexWidth::W16);
PlexorinoDemux demux(PlexWidth::W16);

void setup() {
  mux.begin();
  demux.begin();
  demux.reset();  // optional, but usually nice at startup
}

void loop() {
  for (muxAddr_t i = 0; i < mux.count(); i++) {
    demux.write(i, mux.read(i));
  }
}
