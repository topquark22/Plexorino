/**
 * Interface to 74LS150 16-to-1 multiplexer chip
 */

// This file contains skeleton code for your own projects. Remove this to implement your own use case
#define TEST_CODE

// input pins on the 74LS150 are numbered E0-E15
typedef uint8_t muxPin_t;

// address bus
const uint8_t PIN_ADDR0 = 2; // to 74LS150 pin 15
const uint8_t PIN_ADDR1 = 3; // to 74LS150 pin 14
const uint8_t PIN_ADDR2 = 4; // to 74LS150 pin 13
const uint8_t PIN_ADDR3 = A1; //to 74LS150 pin 11

// data bus
const uint8_t PIN_MUX_DATA_ = A0; // from 74LS150 pin 10 (W, inverted)

// read the input at mux addr. The chip output comes back inverted (pin W, refer to data sheet)
bool readMux16(muxPin_t addr) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);
  digitalWrite(PIN_ADDR3, (addr >> 3) & 0x1);
  return !digitalRead(PIN_MUX_DATA_);
}

 void setup_mux16() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
  pinMode(PIN_ADDR3, OUTPUT);
  // 74LS150 does not have input pullups (refer to data sheet)
  pinMode(PIN_MUX_DATA_, INPUT);
 }

 void setup() {
  setup_mux16();

  // put your setup code here, to run once

#ifdef TEST_CODE
  Serial.begin(9600);
#endif
}

void loop() {
  // put your main code here, to run repeatedly

#ifdef TEST_CODE
  for (muxPin_t addr = 0; addr < 16; addr++) {
    Serial.print(addr);
    Serial.print(F(":"));
    Serial.print(readMux16(addr) ? F("HIGH ") : F("LOW  "));
  }
  Serial.println();
  delay(1000);
#endif TEST_CODE
}
