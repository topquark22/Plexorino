#include <Arduino.h>

#include <Plexorino.h>

/*
 * Blink all demux outputs (16-bit)
 */
void setup() {
  beginDemux(PlexWidth::W16);
  resetDemux();
}

void loop() {
  writeBitsDemux(0xFFFF);
  delay(250);
  writeBitsDemux(0x0000);
  delay(250);
}
