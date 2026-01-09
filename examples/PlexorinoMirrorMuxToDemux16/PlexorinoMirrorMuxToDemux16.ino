#include <Arduino.h>
#include <Plexorino.h>

/*
  Mirror mux inputs to demux outputs (16-bit)
  ------------------------------------------
  Reads all mux channels and writes the same pattern to demux outputs.

  Useful when:
    - you have switches/sensors on mux inputs
    - you want LEDs on demux outputs to reflect state

  If you only have 8-wide hardware, change both begin* calls to W8.
*/

void setup() {
  beginMux(PlexWidth::W16);
  beginDemux(PlexWidth::W16);
  resetDemux();
}

void loop() {
  uint16_t bits = 0;

  for (uint8_t i = 0; i < muxCount(); i++) {
    if (readMux(i)) {
      bits |= (uint16_t(1) << i);
    }
  }

  writeBitsDemux(bits);
  delay(20);
}
