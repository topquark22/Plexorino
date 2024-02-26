/**
 * Interface to LM259 multiplex latch chip
 */

// 74HC259 pins: (note we don't use PWM-capable output pins, SPI or I2C pins)
// 1's bit of output line (pin 1 of 74HG259)
const uint8_t PIN_X0 = 2;
// 2's bit of output line (pin 2 of 74HC259)
const uint8_t PIN_X1 = 4;
// 3's bit of output line (pin 3 of 74HC259)
const uint8_t PIN_X2 = 7;
// output data (pin 13 of 74HC259)
const uint8_t PIN_XDATA = 8;
// output latch data (pin 14 of 74HC259
const uint8_t PIN_XLATCH = A3;

// aliases for address lines on the 74HC259 (pass to write259 function)
const uint8_t X1 = 1;
const uint8_t X2 = 2;
const uint8_t X3 = 3;
const uint8_t X4 = 4;
const uint8_t X5 = 5;
const uint8_t X6 = 6;
const uint8_t X7 = 7;
const uint8_t X8 = 8;

void write259(uint8_t addr, bool value) {
  digitalWrite(PIN_X0, addr & 0x1);
  digitalWrite(PIN_X1, (addr & 0x2) >> 1);
  digitalWrite(PIN_X2, (addr & 0x4) >> 2);
  digitalWrite(PIN_XDATA, value);
  // latch data to output pin
  digitalWrite(PIN_XLATCH, LOW);
  digitalWrite(PIN_XLATCH, HIGH);
}

void writeByte259(uint8_t value) {
  for (uint8_t n = 0; n < 8; n++) {
    write259(n, (value >> n) & 0x1);
  }
}

// reset all output latches to 0
// (Note we don't use the reset pin of the chip; do it manually)
void reset259() {
  for (uint8_t i = 0; i < 8; i++) {
    write259(i, LOW);
  }
}

void setup() {
  pinMode(PIN_X0, OUTPUT);
  pinMode(PIN_X1, OUTPUT);
  pinMode(PIN_X2, OUTPUT);
  pinMode(PIN_XDATA, OUTPUT);
  pinMode(PIN_XLATCH, OUTPUT);
  reset259();
}

void loop() {
  // blink all 8 lines in sequence
  const int ms = 500;
  for (uint8_t addr = 0; addr < 8; addr++) {
    write259(addr, HIGH);
    delay(ms);
    write259(addr, LOW);
  }
}
