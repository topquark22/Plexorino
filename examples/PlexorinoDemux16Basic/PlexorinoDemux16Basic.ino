#include <Arduino.h>
#include <Plexorino.h>

static void chase(uint16_t delayMs) {
  for (uint8_t i = 0; i < demuxCount(); i++) {
    writeDemux(i, true);
    delay(delayMs);
    writeDemux(i, false);
  }
}

void setup() {
  beginDemux(PlexWidth::W16);
  resetDemux();
}

void loop() {
  chase(50);

  // Show writeBitsDemux across 16 lines (low 16 bits used)
  writeBitsDemux(0xAAAA);
  delay(350);
  writeBitsDemux(0x5555);
  delay(350);
  resetDemux();
  delay(350);
}
