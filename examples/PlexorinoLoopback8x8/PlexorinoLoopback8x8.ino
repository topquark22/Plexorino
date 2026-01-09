#include <Arduino.h>
#include <Plexorino.h>

/*
  Loopback test (8x8)
  -------------------
  Intended wiring:
    - Connect each DEMUX output D0..D7 to the corresponding MUX input channel 0..7.
    - beginDemux(W8) drives outputs.
    - beginMux(W8) reads them back.

  If your mux inputs are pulled up/down differently, adjust expectations accordingly.
*/

static void printMismatch(uint8_t ch, bool expected, bool got) {
  Serial.print("Mismatch CH");
  Serial.print(ch);
  Serial.print(" expected=");
  Serial.print(expected ? "1" : "0");
  Serial.print(" got=");
  Serial.println(got ? "1" : "0");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  beginDemux(PlexWidth::W8);
  beginMux(PlexWidth::W8);

  resetDemux();

  Serial.println();
  Serial.println("PlexorinoLoopback8x8");
}

void loop() {
  // One-hot walk, verify each channel.
  for (uint8_t ch = 0; ch < 8; ch++) {
    resetDemux();
    writeDemux(ch, true);
    delay(5); // settle

    bool ok = true;
    for (uint8_t i = 0; i < 8; i++) {
      bool expected = (i == ch);
      bool got = readMux(i);
      if (got != expected) {
        ok = false;
        printMismatch(i, expected, got);
      }
    }

    Serial.print("Step ");
    Serial.print(ch);
    Serial.println(ok ? " OK" : " FAIL");
    delay(200);
  }
}
