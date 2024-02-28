/**
 * Interface to 74LS151 8-to-1 multiplexer chip
 */

const uint8_t PIN_ADDR0 = 2; // addr 1's bit, to mux pin 11
const uint8_t PIN_ADDR1 = 3; // addr 2's bit, to mux pin 10
const uint8_t PIN_ADDR2 = 4; // addr 4's bit, to mux pin 9
const uint8_t PIN_DATA = A0; // data read, to mux pin 5 (noninverted)

// read the input at mux address addr
bool readMux8(uint8_t addr) {
  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);
  return digitalRead(PIN_DATA);
}

 void setup() {
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);
  // 74LS151 already has input pullups (refer to datasheet)
  pinMode(PIN_DATA, INPUT_PULLUP);

  // put your setup code here, to run once
  
}

void loop() {
  // put your main code here, to run repeatedly

}
