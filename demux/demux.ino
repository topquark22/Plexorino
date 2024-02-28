/**
 * Interface to 74HC259 multiplex latch chip
 */

// remove this if you need pin A2 for something else
#define USE_BANK2

#ifdef USE_BANK2
  #define NUM_LINES 16
#else
  #define NUM_LINES 8
#endif

// 74HC259 pins: (note we don't use any SPI or I2C pins)
const uint8_t PIN_XA0 = 2;       // 1's bit of line address (pin 1 of 74HG259)
const uint8_t PIN_XA1 = 3;       // 2's bit of line address (pin 2 of 74HC259)
const uint8_t PIN_XA2 = 4;       // 4's bit of line address (pin 3 of 74HC259)
const uint8_t PIN_XDATA = 8;     // data to latch (pin 13 of 74HC259)
const uint8_t PIN_XLATCH_0 = A3; // latch enable (pin 14 of 74HC259 #1 for outputs 0-7)
#ifdef USE_BANK2
const uint8_t PIN_XLATCH_8 = A2; // latch enable (pin 14 of 74HC259 #2 for outputs 8-15)
#endif

void writeDemux(uint16_t addr, bool value) {
  digitalWrite(PIN_XA0, addr & 0x1);
  digitalWrite(PIN_XA1, (addr & 0x2) >> 1);
  digitalWrite(PIN_XA2, (addr & 0x4) >> 2);
  digitalWrite(PIN_XDATA, value);
  // latch data onto output line
#ifdef USE_BANK2
  if (addr & 0x8) {
    // latch data on chip #2 for lines 8-15
    digitalWrite(PIN_XLATCH_8, LOW);
    digitalWrite(PIN_XLATCH_8, HIGH);
  } else {
    // latch data on chip #1 for lines 0-7
    digitalWrite(PIN_XLATCH_0, LOW);
    digitalWrite(PIN_XLATCH_0, HIGH);
  }
#else
  // latch data on chip #1 for lines 0-7
  digitalWrite(PIN_XLATCH_0, LOW);
  digitalWrite(PIN_XLATCH_0, HIGH);
#endif
}

// write bits of a value across all output lines
void writeBitsDemux(uint16_t value) {
  for (int addr = 0; addr < NUM_LINES; addr++) {
    writeDemux(addr, (value >> addr) & 0x1);
  }
}

// reset all output latches to 0
// (Note we don't use the reset pin of the chip; do it manually)
void reset() {
  writeBitsDemux(0);
}

void setupDemux() {
  pinMode(PIN_XA0, OUTPUT);
  pinMode(PIN_XA1, OUTPUT);
  pinMode(PIN_XA2, OUTPUT);
  pinMode(PIN_XDATA, OUTPUT);
  pinMode(PIN_XLATCH_0, OUTPUT);
#ifdef USE_BANK2
  pinMode(PIN_XLATCH_8, OUTPUT);
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
  for (int addr = 0; addr < NUM_LINES; addr++) {
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
