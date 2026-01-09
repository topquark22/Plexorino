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
  beginDemux(PlexWidth::W8);
  resetDemux();
}

void loop() {
  chase(60);

  // Also show writeBitsDemux on 8 lines (low 8 bits used)
  writeBitsDemux(0xAA); // 10101010
  delay(300);
  writeBitsDemux(0x55); // 01010101
  delay(300);
  resetDemux();
  delay(300);
}
