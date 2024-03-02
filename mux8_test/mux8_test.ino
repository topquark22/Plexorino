/**
 * Interface to 74LS151 8-to-1 multiplexer chip
 */

const uint8_t PIN_ADDR0 = 2; // addr 1's bit, to mux pin 11
const uint8_t PIN_ADDR1 = 3; // addr 2's bit, to mux pin 10
const uint8_t PIN_ADDR2 = 4; // addr 4's bit, to mux pin 9
const uint8_t PIN_DATA = A0; // data read, to mux pin 5 (noninverted)

const int PIN_OUT = 6;

// read the input at mux address addr
bool readMux8(uint8_t addr) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);
  return digitalRead(PIN_DATA);
}

 void setup_mux8() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
  // 74LS151 does not have input pullups (refer to datasheet)
  pinMode(PIN_DATA, INPUT);
 }

 void setup() {
  setup_mux8();
  pinMode(PIN_OUT, OUTPUT);
}

void loop() {
  bool value = readMux8(6);
  digitalWrite(PIN_OUT, value);
}
