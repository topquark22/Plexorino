/**
 * Interface to:
 *   74HC259 8-output addressable latch (demultiplexer)
 *   74LS151 8-input multiplexer
 *   74LS150 16-input multiplexer
 */
#include "plexorino.h"

void writeDemux(muxAddr_t addr, bool value) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr & 0x2) >> 1);
  digitalWrite(PIN_ADDR2, (addr & 0x4) >> 2);
  digitalWrite(PIN_DEMUX_DATA, value);
  // latch data onto output line. The chip timings are in ns, so we should be ok
#ifdef DEMUX16
  if (addr & 0x8) {
    // latch data on Chip 1 for addresses 8-15
    digitalWrite(PIN_LATCH1, LOW);
    digitalWrite(PIN_LATCH1, HIGH);
  } else {
    // latch data on Chip 0 for addresses 0-7
    digitalWrite(PIN_LATCH0, LOW);
    digitalWrite(PIN_LATCH0, HIGH);
  }
#else
  // latch data on Chip 0 for addresses 0-7
  digitalWrite(PIN_LATCH0, LOW);
  digitalWrite(PIN_LATCH0, HIGH);
#endif
}

// read the input at mux addr. The output from the chip comes back inverted (pin W, refer to data sheet)
bool readMux(muxAddr_t addr) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);
#ifdef MUX16
  digitalWrite(PIN_ADDR3, (addr >> 3) & 0x1);
#endif
  return !digitalRead(PIN_MUX_DATA_);
}

void writeBitsDemux(uint16_t bits) {
  for (muxAddr_t addr = 0; addr < DEMUX_CT; addr++) {
    writeDemux(addr, (bits >> addr) & 0x1);
  }
}

// reset all output latches to 0
// (Note we don't use the reset pin of the chip; do it manually)
void resetDemux() {
  writeBitsDemux(0);
}

void setupMux() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
#ifdef MUX16
  pinMode(PIN_ADDR3, OUTPUT);
#endif
  pinMode(PIN_MUX_DATA_, INPUT);

}

void setupDemux() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
  pinMode(PIN_DEMUX_DATA, OUTPUT);
  pinMode(PIN_LATCH0, OUTPUT);
#ifdef DEMUX16
  pinMode(PIN_LATCH1, OUTPUT);
#endif
  resetDemux();
}
