#include <Arduino.h>
#include <Plexorino.h>

/*
  Loopback test (16x16)
  ---------------------
  Intended wiring:
    - Connect each DEMUX output D0..D15 to the corresponding MUX input channel 0..15.
    - beginDemux(W16) drives outputs.
    - beginMux(W16) reads them back.

  Notes:
    - readMux() is inverted relative to the mux output pin wiring (library already inverts),
      so "got" should match "expected" in normal use.
*/

static void printMismatch(uint8_t ch, bool expected, bool got) {
  Serial.print("Mismatch CH");
  if (ch < 10) Serial.print('0');
  Serial.print(ch);
  Serial.print(" expected=");
  Serial.print(expected ? "1" : "0");
  Serial.print(" got=");
  Serial.println(got ? "1" : "0");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  beginDemux(PlexWidth::W16);
  beginMux(PlexWidth::W16);

  resetDemux();

  Serial.println();
  Serial.println("PlexorinoLoopback16x16");
}

void loop() {
  // One-hot walk, verify each channel.
  for (uint8_t ch = 0; ch < 16; ch++) {
    resetDemux();
    writeDemux(ch, true);
    delay(5); // settle

    bool ok = true;
    for (uint8_t i = 0; i < 16; i++) {
      bool expected = (i == ch);
      bool got = readMux(i);
      if (got != expected) {
        ok = false;
        printMismatch(i, expected, got);
      }
    }

    Serial.print("Step ");
    if (ch < 10) Serial.print('0');
    Serial.print(ch);
    Serial.println(ok ? " OK" : " FAIL");
    delay(200);
  }
}
