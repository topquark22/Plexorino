/**
 * Interface to LM259 multiplex latch chip
 */

// 74HC259 pins: (note we don't use any PWM-capable output pins, SPI or I2C pins)
const uint8_t PIN_XA0 = 2;       // 1's bit of output line (pin 1 of 74HG259)
const uint8_t PIN_XA1 = 4;       // 2's bit of output line (pin 2 of 74HC259)
const uint8_t PIN_XA2 = 7;       // 4's bit of output line (pin 3 of 74HC259)
const uint8_t PIN_XDATA = 8;     // output data (pin 13 of 74HC259)
const uint8_t PIN_XLATCH_0 = A3; // output latch (pin 14 of 74HC259 #1 for outputs 0-7)
const uint8_t PIN_XLATCH_8 = A2; // output latch (pin 14 of 74HC259 #2 for outputs 8-15)

void write259(uint16_t addr, bool value) {
  digitalWrite(PIN_XA0, addr & 0x1);
  digitalWrite(PIN_XA1, (addr & 0x2) >> 1);
  digitalWrite(PIN_XA2, (addr & 0x4) >> 2);
  digitalWrite(PIN_XDATA, value);
  // latch data to output pin
  if (addr & 0x8) {
    // latch data on chip #1 for lines 8-15
    digitalWrite(PIN_XLATCH_8, LOW);
    digitalWrite(PIN_XLATCH_8, HIGH);
  } else {
    // latch data on chip #2 for lines 0-7
    digitalWrite(PIN_XLATCH_0, LOW);
    digitalWrite(PIN_XLATCH_0, HIGH);
  }
}

// write a 16-bit value across all 16 output lines
void writeBits(uint16_t value) {
  for (int addr = 0; addr < 16; addr++) {
    write259(addr, (value >> addr) & 0x1);
  }
}

// reset all output latches to 0
// (Note we don't use the reset pin of the chip; do it manually)
void reset() {
  writeBits(0);
}

void setup() {
  pinMode(PIN_XA0, OUTPUT);
  pinMode(PIN_XA1, OUTPUT);
  pinMode(PIN_XA2, OUTPUT);
  pinMode(PIN_XDATA, OUTPUT);
  pinMode(PIN_XLATCH_0, OUTPUT);
  pinMode(PIN_XLATCH_8, OUTPUT);
  reset();
}

void loop() {
  // blink all 8 lines in sequence
  const int ms = 500;
  for (int addr = 0; addr < 16; addr++) {
    write259(addr, HIGH);
    delay(ms);
    write259(addr, LOW);
  }
}
