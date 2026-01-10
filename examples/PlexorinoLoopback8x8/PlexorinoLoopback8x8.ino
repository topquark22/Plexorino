// PlexorinoLoopback8x8.ino
#include <Arduino.h>
#include <Plexorino.h>

/*
  PlexorinoLoopback8x8
  -------------------
  Loopback test for 8-bit Plexorino hardware.

  Hardware:
    - Mux:   74LS151 (8 inputs)
    - Demux: 74HC259 (8 outputs)

  Wiring:
    - Each demux output is wired back to the corresponding mux input.

  Behaviour:
    - Walks a single HIGH bit across demux outputs
    - Reads back the mux inputs
    - Verifies loopback by observing the same bit position

  Notes:
    - Uses both PlexorinoMux and PlexorinoDemux
    - Shared address lines are driven only during each read/write
      and released to high-Z immediately afterward
*/

PlexorinoMux   mux(PlexWidth::W8);
PlexorinoDemux demux(PlexWidth::W8);

void setup() {
  Serial.begin(115200);

  mux.begin();
  demux.begin();
  demux.reset();

  Serial.println(F("PlexorinoLoopback8x8 starting"));
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
