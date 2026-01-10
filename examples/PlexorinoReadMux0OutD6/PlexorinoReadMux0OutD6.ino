#include <Arduino.h>
#include <Plexorino.h>

const uint8_t PIN_OUT = 6;

void setup() {
  pinMode(PIN_OUT, OUTPUT);
  beginMux(PlexWidth::W16);
}

void loop() {
  digitalWrite(PIN_OUT, readMux(0));
}
