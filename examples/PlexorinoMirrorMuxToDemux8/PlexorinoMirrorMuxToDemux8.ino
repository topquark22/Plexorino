// PlexorinoMirrorMuxToDemux8.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoMirrorMuxToDemux8
  -------------------------
  Mirrors 8 mux inputs to 8 demux outputs.

  Hardware:
    - Mux: 74LS151 (8:1)
    - Demux: 74HC259 (8 outputs)

  Notes:
    - Uses the new split classes: PlexorinoMux / PlexorinoDemux
    - Width is selected at runtime (W8 here)
    - Shared address lines are driven only during each read/write and then released to INPUT
*/

PlexorinoMux   mux(PlexWidth::W8);
PlexorinoDemux demux(PlexWidth::W8);

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
