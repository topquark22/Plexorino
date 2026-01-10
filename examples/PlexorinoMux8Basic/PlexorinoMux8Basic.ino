// PlexorinoMux8Basic.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoMux8Basic
  ------------------
  Reads all 8 mux channels (74LS151) and prints them to Serial.

  Notes:
    - Uses the split-class API: PlexorinoMux
    - Explicit begin()
    - Uses muxAddr_t for address variables
*/

PlexorinoMux mux(PlexWidth::W8);

void setup() {
  mux.begin();
  Serial.begin(115200);
  Serial.println(F("PlexorinoMux8Basic"));
}

void loop() {
  for (muxAddr_t i = 0; i < mux.count(); i++) {
    Serial.print(mux.read(i) ? '1' : '0');
    if (i != (muxAddr_t)(mux.count() - 1)) Serial.print(' ');
  }
  Serial.println();
  delay(200);
}
