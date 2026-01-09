#include <Arduino.h>
#include <Plexorino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for serial on some boards */ }

  beginMux(PlexWidth::W8);

  Serial.println();
  Serial.println("PlexorinoMux8Basic");
  Serial.println("Mux width: 8");
}

void loop() {
  for (uint8_t i = 0; i < muxCount(); i++) {
    Serial.print("CH");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(readMux(i) ? "HIGH" : "LOW");
  }
  Serial.println("---");
  delay(500);
}
