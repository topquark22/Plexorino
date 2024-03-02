/**
 * Interface to 74LS150 16-to-1 multiplexer chip
 */

// address bus
const uint8_t PIN_ADDR0 = 2; // mux pin 15
const uint8_t PIN_ADDR1 = 3; // mux pin 14
const uint8_t PIN_ADDR2 = 4; // mux pin 13
const uint8_t PIN_ADDR3 = A1; //mux pin 11
// data bus
const uint8_t PIN_DATA = A0; // mux pin 10

// read the input at mux addr. The value is inverted
bool readMux16(uint8_t addr) {
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

 void setup() {
  setup_mux16();

  // put your setup code here, to run once
  
}

void loop() {
  // put your main code here, to run repeatedly

}
