#pragma once
/**
 * Plexorino: hardcoded-pin interface to:
 *   - 74HC259 8-bit addressable latch (demultiplexed outputs)
 *   - 74LS151 8-input multiplexer
 *   - 74LS150 16-input multiplexer
 *
 * Key refactor:
 *   - No compile flags to choose 8 vs 16.
 *   - You select width at runtime via beginMux()/beginDemux().
 *   - Pins remain hardcoded (by design).
 */

#include <Arduino.h>

// Outputs on 74HC259 chip #0 are D0-D7; on chip #1 are D8-D15.
using muxAddr_t = uint8_t;

enum class PlexWidth : uint8_t { W8 = 8, W16 = 16 };

// -------------------------
// Hardcoded pin assignment
// -------------------------
// 74HC259 address pins: (note we don't use any SPI or I2C pins, leaving them free)
constexpr uint8_t PIN_ADDR0     = 2;   // 1's bit of mux/demux address (74HC259 pin 1; 74LS151 pin 11; 74LS150 pin 15)
constexpr uint8_t PIN_ADDR1     = 3;   // 2's bit of mux/demux address (74HC259 pin 2; 74LS151 pin 10; 74LS150 pin 14)
constexpr uint8_t PIN_ADDR2     = 4;   // 4's bit of mux/demux address (74HC259 pin 3; 74LS151 pin 9;  74LS150 pin 13)

// 16-bit mux only (74LS150): 8's address bit
constexpr uint8_t PIN_ADDR3     = A1;  // 74LS150 pin 11 (A3)

// Mux data input (inverted from chip output)
constexpr uint8_t PIN_MUX_DATA_ = A0;  // 74LS151 pin 5/6 output (W); 74LS150 pin 10 output (W)

// Demux data and latch enables
constexpr uint8_t PIN_DEMUX_DATA = 5;  // 74HC259 pin 13 (D)
constexpr uint8_t PIN_LATCH0     = A3; // latch enable for outputs 0-7 (74HC259 #0 pin 14 / G)
constexpr uint8_t PIN_LATCH1     = A2; // latch enable for outputs 8-15 (74HC259 #1 pin 14 / G) -- only used in 16-bit demux mode

// -------------------------
// Initialization / mode
// -------------------------
void beginMux(PlexWidth width = PlexWidth::W16);
void beginDemux(PlexWidth width = PlexWidth::W16);

PlexWidth muxWidth();
PlexWidth demuxWidth();

uint8_t muxCount();    // 8 or 16
uint8_t demuxCount();  // 8 or 16

// -------------------------
// Core operations
// -------------------------

// Read the input at mux address. Output from the mux comes back inverted.
bool readMux(muxAddr_t addr);

// Write a single demux output line.
void writeDemux(muxAddr_t addr, bool value);

// Write bits of a value across all output lines (uses low demuxCount() bits).
void writeBitsDemux(uint16_t bits);

// Reset all output latches to 0 (done manually; does not use the chip reset pin).
void resetDemux();

// -------------------------
// Backward-compat aliases
// -------------------------
// These preserve older sketch behavior: they default to 16-bit mode.
inline void setupMux()   { beginMux(PlexWidth::W16); }
inline void setupDemux() { beginDemux(PlexWidth::W16); }
