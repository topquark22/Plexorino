// PlexorinoLoopback16x16.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoLoopback16x16
  ---------------------
  Loopback test for 16-bit Plexorino hardware.

  Hardware:
    - Mux:   74LS150 (16 inputs)
    - Demux: two 74HC259 chips (16 outputs total)

  Wiring:
    - Each demux output is wired back to the corresponding mux input.

  Behaviour:
    - Walks a single HIGH bit across demux outputs (0..15)
    - Reads back all mux inputs
    - Prints the observed pattern to Serial

  Notes:
    - Uses both PlexorinoMux and PlexorinoDemux
    - Shared address lines (ADDR0..ADDR3) are driven only during each
      read/write and released to high-Z immediately afterward
    - Useful for validating full 16×16 wiring integrity
*/

PlexorinoMux   mux(PlexWidth::W16);
PlexorinoDemux demux(PlexWidth::W16);

void setup() {
  Serial.begin(115200);

  mux.begin();
  demux.begin();
  demux.reset();

  Serial.println(F("PlexorinoLoopback16x16 starting"));
}

void loop() {
  for (uint8_t i = 0; i < demux.count(); i++) {
    // Drive exactly one output HIGH
    demux.reset();
    demux.write(i, true);

    // Small settle time for wiring / logic
    delay(2);

    // Read back all mux inputs
    Serial.print(F("Out "));
    Serial.print(i);
    Serial.print(F(" -> In: "));

    for (uint8_t j = 0; j < mux.count(); j++) {
      Serial.print(mux.read(j) ? '1' : '0');
      if (j != mux.count() - 1) Serial.print(' ');
    }

    Serial.println();
    delay(200);
  }

  Serial.println();
}
