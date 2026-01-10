#include <Arduino.h>

#include <Plexorino.h>

/*
 * Blink all demux outputs (8-bit)
 */
void setup() {
  beginDemux(PlexWidth::W8);
  resetDemux();
}

void loop() {
  writeBitsDemux(0xFF);
  delay(250);
  writeBitsDemux(0x00);
  delay(250);
}
