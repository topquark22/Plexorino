/**
 * Interface to 74LS150 16-to-1 multiplexer chip
 */

const uint8_t PIN_MA0 = 2; // addr 1's bit, to mux pin 15
const uint8_t PIN_MA1 = 3; // addr 2's bit, to mux pin 14
const uint8_t PIN_MA2 = 4; // addr 4's bit, to mux pin 13
const uint8_t PIN_MA3 = A1; // addr 8's bit, to mux pin 11
const uint8_t PIN_MD_ = A0; // data read, to mux pin 10 (inverted)

// read the input at mux address addr
bool read154(uint8_t addr) {
  digitalWrite(PIN_MA0, addr & 0x1);
  digitalWrite(PIN_MA1, (addr >> 1) & 0x1);
  digitalWrite(PIN_MA2, (addr >> 2) & 0x1);
  digitalWrite(PIN_MA3, (addr >> 3) & 0x1);
  return !digitalRead(PIN_MD_);
}

 void setup() {
  pinMode(PIN_MA0, OUTPUT);
  pinMode(PIN_MA1, OUTPUT);
  pinMode(PIN_MA2, OUTPUT);
  // 74LS151 already has input pullups
  pinMode(PIN_MD_, INPUT_PULLUP);

  // put your setup code here, to run once
  
}

void loop() {
  // put your main code here, to run repeatedly

}
