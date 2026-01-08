#pragma once

/**
 * Interface to 74HC259 8-bit addressable latch, 74LS151 8-bit multiplexer, 74LS150 16-bit multiplexer
 */

#include <Arduino.h>

// If your mux use case is 8-input (74LS151) only and you want to use pin A1
// for something else, then define MUX8_ONLY at compile time. But in any case,
// it will still work; you just won't be able to use pin A1 for anything else
// because it will be dedicated to address line 3 for the 74LS150.
#ifndef MUX8_ONLY
  #define MUX16
#endif

// If your demux use case is 8-output (1x 74HC259) and you want to use A2
// for something else, then define DEMUX8_ONLY at compile time. This will
// free up pin A2. Otherwise it will still work; you will just not be able
// to use A2 for anything else.
#ifndef DEMUX8_ONLY
  #define DEMUX16
#endif

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
// output pins on the 74HC259 chip #0 are numbered D0-D7
// output pins on the 74HC259 chip #1 are numbered D8-D15
typedef uint8_t muxAddr_t;

// 74HC259 pins: (note we don't use any SPI or I2C pins, leaving them free)
constexpr uint8_t PIN_ADDR0 = 2;       // 1's bit of mux/demux address (pin 1 of 74HC259; pin 11 of 74LS151; pin 15 of 74LS150)
constexpr uint8_t PIN_ADDR1 = 3;       // 2's bit of mux/demux address (pin 2 of 74HC259; pin 10 of 74LS151; pin 14 of 74LS150)
constexpr uint8_t PIN_ADDR2 = 4;       // 4's bit of mux/demux address (pin 3 of 74HC259; pin 9 of 74LS151; pin 13 of 74LS150)
#ifdef MUX16
constexpr uint8_t PIN_ADDR3 = A1;      // 8's bit of mux address (pin 11 of 74HS150)
#endif
constexpr uint8_t PIN_MUX_DATA_ = A0;  // inverted data from mux (pin 6 of 74LS151; pin 10 of 74LS150)

constexpr uint8_t PIN_DEMUX_DATA = 5;  // data to demux (pin 13 of 74HC259)
constexpr uint8_t PIN_LATCH0 = A3; // latch enable for outputs 0-7 (pin 14 of 74HC259 #0)
#ifdef DEMUX16
constexpr uint8_t PIN_LATCH1 = A2; // latch enable for outputs 8-15 (pin 14 of 74HC259 #1)
#endif

bool readMux(muxAddr_t addr);

void writeDemux(muxAddr_t addr, bool value);

// write bits of a value across all output lines
void writeBitsDemux(uint16_t bits);

// reset all output latches to 0
void resetDemux();

void setupDemux();

void setupMux();
