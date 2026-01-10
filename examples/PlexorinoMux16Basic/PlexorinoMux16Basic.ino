// PlexorinoMux16Basic.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoMux16Basic
  ------------------
  Reads all 16 mux channels (74LS150) and prints them to Serial.

  Notes:
    - Uses the split-class API: PlexorinoMux
    - Explicit begin()
    - Uses muxAddr_t for address variables
*/

PlexorinoMux mux(PlexWidth::W16);

void setup() {
  mux.begin();
  Serial.begin(115200);
  Serial.println(F("PlexorinoMux16Basic"));
}

void loop() {
  for (muxAddr_t i = 0; i < mux.count(); i++) {
    Serial.print(mux.read(i) ? '1' : '0');
    if (i != (muxAddr_t)(mux.count() - 1)) Serial.print(' ');
  }
  Serial.println();
  delay(200);
}
