#include <Arduino.h>
#include <Plexorino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for serial on some boards */ }

  beginMux(PlexWidth::W16);

  Serial.println();
  Serial.println("PlexorinoMux16Basic");
  Serial.println("Mux width: 16");
}

void loop() {
  for (uint8_t i = 0; i < muxCount(); i++) {
    Serial.print("CH");
    if (i < 10) Serial.print('0');
    Serial.print(i);
    Serial.print(": ");
    Serial.println(readMux(i) ? "HIGH" : "LOW");
  }
  Serial.println("---");
  delay(500);
}
