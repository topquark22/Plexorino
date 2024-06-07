/**
 * Interface to:
 *   74LS150 16-to-1 multiplexer chip
 *   74LS151 8-to-1 multiplexer chip
 *   74HC259 8-bit demultiplexer chip
 */

#include "plexorino.h"

void setup() {
  setupDemux();
  setupMux();

  // put your setup code here, to run once
  Serial.begin(9600);
}

void loop() {
  for (muxAddr_t addr = 0; addr < MUX_CT; addr++) {
    writeDemux(addr % DEMUX_CT, !readMux(addr));
  }
}
/*
void loop() {
  // put your main code here, to run repeatedly

// mux test routine
  for (muxAddr_t addr = 0; addr < MUX_CT; addr++) {
    Serial.print(F("E"));
    Serial.print(addr);
    Serial.print(F(":"));
    Serial.print(readMux(addr) ? F("HIGH ") : F("LOW  "));
  }
  Serial.println();
  delay(1000);

}
*/
