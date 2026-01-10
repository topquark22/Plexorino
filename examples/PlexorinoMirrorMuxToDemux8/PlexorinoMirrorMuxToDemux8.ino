#include <Arduino.h>
#include <Plexorino.h>

/*
  Mirror mux inputs to demux outputs (8-bit)
  ------------------------------------------
  Reads all mux channels and writes the same bits to demux outputs.

  Useful when:
    - you have switches/sensors on mux inputs
    - you want LEDs on demux outputs to reflect state

  If you have 16-wide hardware, change both begin* calls to W16.
*/

void setup() {
  beginMux(PlexWidth::W8);
  beginDemux(PlexWidth::W8);
  resetDemux();
}

void loop() {
  for (uint8_t i = 0; i < muxCount(); i++) {
    writeDemux(i, readMux(i));
  }
}
