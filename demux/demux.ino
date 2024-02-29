/**
 * Interface to 74HC259 multiplex latch
 */

// remove this if your use-case is 8-output
#define USE_CHIP1

#ifdef USE_CHIP1
  #define MUX_CT 16
#else
  #define MUX_CT 8
#endif

// 74HC259 pins: (note we don't use any SPI or I2C pins)
const uint8_t PIN_ADDR0 = 2;       // 1's bit of line address (pin 1 of 74HG259)
const uint8_t PIN_ADDR1 = 3;       // 2's bit of line address (pin 2 of 74HC259)
const uint8_t PIN_ADDR2 = 4;       // 4's bit of line address (pin 3 of 74HC259)
const uint8_t PIN_DATA = 8;     // data to latch (pin 13 of 74HC259)
const uint8_t PIN_LATCH0 = A3; // latch enable (pin 14 of 74HC259 #1 for outputs 0-7)
#ifdef USE_CHIP1
const uint8_t PIN_LATCH1 = A2; // latch enable (pin 14 of 74HC259 #2 for outputs 8-15)
#endif

void writeDemux(uint16_t addr, bool value) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr & 0x2) >> 1);
  digitalWrite(PIN_ADDR2, (addr & 0x4) >> 2);
  digitalWrite(PIN_DATA, value);
  // latch data onto output line. The chip timings are in ns, so we should be ok
#ifdef USE_CHIP1
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

// write bits of a value across all output lines
void writeBitsDemux(uint16_t value) {
  for (int addr = 0; addr < MUX_CT; addr++) {
    writeDemux(addr, (value >> addr) & 0x1);
  }
}

// reset all output latches to 0
// (Note we don't use the reset pin of the chip; do it manually)
void reset() {
  writeBitsDemux(0);
}

void setupDemux() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_LATCH0, OUTPUT);
#ifdef USE_CHIP1
  pinMode(PIN_LATCH1, OUTPUT);
#endif
  reset();
}

void setup() {
  setupDemux();

  // Put your custom setup code here ...
  
}

// blink all lines in sequence
void testRoutine() {
  const int ms = 500;
  for (int addr = 0; addr < MUX_CT; addr++) {
    writeDemux(addr, HIGH);
    delay(ms);
    writeDemux(addr, LOW);
    delay(ms);
  }
}

void loop() {

  // Put your custom loop code here ...

  testRoutine(); 
}
