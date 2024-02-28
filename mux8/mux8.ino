/**
 * Interface to 74LS151 8-to-1 multiplexer chip
 */

const uint8_t PIN_MA0 = 3; // addr 1's bit, to mux pin 11
const uint8_t PIN_MA1 = 5; // addr 2's bit, to mux pin 10
const uint8_t PIN_MA2 = 6; // addr 4's bit, to mux pin 9
const uint8_t PIN_MD = A0; // data read, to mux pin 5 (noninverted)

// read the input at mux address addr
bool read151(uint8_t addr) {
  digitalWrite(PIN_MA0, addr & 0x1);
  digitalWrite(PIN_MA1, (addr >> 1) & 0x1);
  digitalWrite(PIN_MA2, (addr >> 2) & 0x1);
  return digitalRead(PIN_MD);
}

 void setup() {
  pinMode(PIN_MA0, OUTPUT);
  pinMode(PIN_MA1, OUTPUT);
  pinMode(PIN_MA2, OUTPUT);
  // 74LS151 already has input pullups
  pinMode(PIN_MD, INPUT_PULLUP);

  // put your setup code here, to run once
  
}

void loop() {
  // put your main code here, to run repeatedly

}