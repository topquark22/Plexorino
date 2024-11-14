/**
 * Test code for interface to:
 *   74LS150 16-to-1 multiplexer chip
 *   74LS151 8-to-1 multiplexer chip
 *   74HC259 8-bit demultiplexer chip
 */

#include <plexorino.h>

void setup() {
  setupDemux();
  setupMux();

  // put your setup code here, to run once
  Serial.begin(9600);
}

void loop() {
  // start by indicating the beginning of the sequence with 3 short blinks
  for (int i = 0; i < 3; i++) {
    writeDemux(0, HIGH);
    delay(50);
    writeDemux(0, LOW);
    delay(50);
  }
  delay(1000);

  // read each mux input in sequence. Output a short blink for a 0, a long blink for a 1
  for (int addr = 0; addr < MUX_CT; addr++) {
    bool v = readMux(addr);
    Serial.print(F("E"));
    Serial.print(addr);
    Serial.print(F(":"));
    Serial.print(v ? F("HIGH ") : F("LOW  "));
    int t = !v ? 750 : 100;
    writeDemux(0, HIGH);
    delay(t);
    writeDemux(0, LOW);
    delay(1000 - t);
  }
  delay(750);
  Serial.println();
}
