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
const uint8_t PIN_DATA = A0; // from 74LS150 pin 10

#ifdef TEST_CODE
// echo the mux output to an Arduino pin
const uint8_t PIN_ECHO_OUT = 5;
#endif

// read the input at mux addr. The value is inverted
bool readMux16(muxPin_t addr) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);
  digitalWrite(PIN_ADDR3, (addr >> 3) & 0x1);
  return !digitalRead(PIN_DATA);
}

 void setup_mux16() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
  pinMode(PIN_ADDR3, OUTPUT);
  // 74LS150 does not have input pullups (refer to data sheet)
  pinMode(PIN_DATA, INPUT);
 }

#ifdef TEST_CODE
muxPin_t muxPin = 0; // default E0
#endif

 void setup() {
  setup_mux16();

  // put your setup code here, to run once

#ifdef TEST_CODE
  pinMode(PIN_ECHO_OUT, OUTPUT);
  Serial.begin(9600);
  Serial.print(F("Enter mux pin to test, default "));
  Serial.println(muxPin);
#endif
}

void loop() {
  // put your main code here, to run repeatedly

#ifdef TEST_CODE
  if (Serial.available()) {
    muxPin = Serial.readString().toInt();
    Serial.print(F("Testing pin "));
    Serial.println(muxPin);
    Serial.println(F("Enter next pin to test:"));
  }
  digitalWrite(PIN_ECHO_OUT, readMux16(muxPin));
#endif TEST_CODE
}
