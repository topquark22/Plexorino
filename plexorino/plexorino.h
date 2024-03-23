/**
 * Interface to 74HC259 multiplex latch
 */

#ifndef PLEXORINO_H
#define PLEXORINO_H

#include <Arduino.h>

// Comment this if your mux use case is 8-input (74LS151)
// Leave uncommented if your use case is 16-input (74LS150)
#define MUX16

// Comment this if your demux use-case is 8-output (1x 74HC259)
// Leave uncommented if your use case is 16-output (2x 74HC259)
#define DEMUX16

#ifdef MUX16
  #define MUX_CT 16
#else
  #define MUX_CT 8
#endif

#ifdef DEMUX16
  #define DEMUX_CT 16
#else
  #define DEMUX_CT 8
#endif

// input pins on the 74LS151 are numbered E0-E7
// input pins on the 74LS150 are numbered E0-E15
// output pins on the 74HC259 are numbered D0-D7
typedef uint8_t muxAddr_t;

// 74HC259 pins: (note we don't lap any SPI or I2C pins, leaving them free)
const PROGMEM uint8_t PIN_ADDR0 = 2;       // 1's bit of mux/demux address (pin 1 of 74HG259; pin 11 of 74LS151; pin 15 of 74LS150)
const PROGMEM uint8_t PIN_ADDR1 = 3;       // 2's bit of mux/demux address (pin 2 of 74HC259; pin 10 of 74LS151; pin 14 of 74LS150)
const PROGMEM uint8_t PIN_ADDR2 = 4;       // 4's bit of mux/demux address (pin 3 of 74HC259; pin 9 of 74LS151; pin 13 of 74LS150)
#ifdef MUX16
const PROGMEM uint8_t PIN_ADDR3 = A1;      // 8's bit of mux address (pin 11 of 74HS150)
#endif
const PROGMEM uint8_t PIN_MUX_DATA_ = A0;  // inverted data from mux (pin 6 of 74LS151; pin 10 of 74LS150)

const PROGMEM uint8_t PIN_DEMUX_DATA = 5;  // data to demux (pin 13 of 74HC259)
const PROGMEM uint8_t PIN_LATCH0 = A3; // latch enable for outputs 0-7 (pin 14 of 74HC259 #0)
#ifdef DEMUX16
const PROGMEM uint8_t PIN_LATCH1 = A2; // latch enable for outputs 8-15 (pin 14 of 74HC259 #1)
#endif

bool readMux(muxAddr_t addr);

void writeDemux(muxAddr_t addr, bool value);

// write bits of a value across all output lines
void writeBitsDemux(uint16_t bits);

// reset all output latches to 0
void resetDemux();

void setupDemux();

void setupMux();

#endif  // PLEXORINO_H
