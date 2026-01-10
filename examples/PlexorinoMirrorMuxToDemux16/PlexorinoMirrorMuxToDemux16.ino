#include <Arduino.h>
#include <Plexorino.h>


#if defined(__AVR__)
uint16_t boots __attribute__((section(".noinit")));
uint8_t  mcusr_mirror __attribute__((section(".noinit")));

void get_mcusr(void) __attribute__((naked)) __attribute__((section(".init3")));
void get_mcusr(void) {
  mcusr_mirror = MCUSR;
  MCUSR = 0;
}
#endif

/*
  Mirror mux inputs to demux outputs (16-bit)
  ------------------------------------------
  Reads all mux channels and writes the same bits to demux outputs.

  Useful when:
    - you have switches/sensors on mux inputs
    - you want LEDs on demux outputs to reflect state

  If you have 8-wide hardware, change both begin* calls to W8.
*/

void setup() {
  beginMux(PlexWidth::W16);
  beginDemux(PlexWidth::W16);
  resetDemux();
}

void loop() {
  for (uint8_t i = 0; i < muxCount(); i++) {
    writeDemux(i, readMux(i));
  }
}
