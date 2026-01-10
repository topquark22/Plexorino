#pragma once
/*
 * Plexorino.h
 *
 * Plexorino is a small Arduino library for:
 *  - Multiplexing GPIO inputs using 74LS151 (8) or 74LS150 (16)
 *  - Demultiplexing GPIO outputs using 74HC259 (8) or two 74HC259 (16)
 *
 * Refactor notes:
 *  - No compile-time width flags.
 *  - Two independent classes: PlexorinoMux and PlexorinoDemux.
 *  - Hardcoded pinout by design.
 *  - Address lines ADDR0..ADDR2 are shared.
 *  - ADDR3 is driven only by the mux in W16 mode.
 *  - BOTH classes release ALL address lines (including ADDR3) to high-Z (INPUT)
 *    when idle, to avoid contention when mux and demux coexist or when external
 *    circuitry shares the bus.
 *
 * Platform: intended for Arduino AVR (e.g., Uno/Nano), but generally portable.
 */

#include <Arduino.h>

// -------------------------
// Types
// -------------------------

enum class PlexWidth : uint8_t {
  W8  = 8,
  W16 = 16
};

// Address type for mux/demux channels.
//  - W8  valid range:  0..7
//  - W16 valid range:  0..15
using muxAddr_t = uint8_t;

// -------------------------
// Hardcoded pinout (by design)
// -------------------------
//
// Shared address lines (mux + demux)
static constexpr uint8_t PIN_ADDR0 = 2;  // D2
static constexpr uint8_t PIN_ADDR1 = 3;  // D3
static constexpr uint8_t PIN_ADDR2 = 4;  // D4

// Address bit 3:
//  - Driven by PlexorinoMux in W16 mode
//  - Released to INPUT (high-Z) by BOTH classes when idle
static constexpr uint8_t PIN_ADDR3 = A1; // mux address bit 3 (W16 mux only)

// Mux-only data pin
static constexpr uint8_t PIN_MUX_DATA_ = A0;  // mux output (read inverted)

// Demux-only pins
static constexpr uint8_t PIN_DEMUX_DATA = 5;   // D5: data into 74HC259
static constexpr uint8_t PIN_LATCH0     = A3;  // outputs 0..7 latch enable
static constexpr uint8_t PIN_LATCH1     = A2;  // outputs 8..15 latch enable (W16 demux only)

// -------------------------
// PlexorinoMux
// -------------------------
//
// Reads a single mux channel via 74LS151 (W8) or 74LS150 (W16).
// Output is read inverted: read(addr) returns !digitalRead(PIN_MUX_DATA).
//
// Address lines are driven only during read() and then released to INPUT.
class PlexorinoMux {
public:
  explicit PlexorinoMux(PlexWidth width = PlexWidth::W16);

  // Configure only mux-related pins (shared address lines are driven per-read).
  void begin();

  // Returns true once begin() has been called.
  bool begun() const;

  PlexWidth width() const;
  uint8_t count() const;   // 8 or 16 depending on width()

  // Read a mux channel. Returns false if not begun() or addr out of range.
  bool read(muxAddr_t addr) const;

private:
  PlexWidth width_;
  bool begun_;
};

// -------------------------
// PlexorinoDemux
// -------------------------
//
// Writes a single demux output via 74HC259 (W8) or two 74HC259 (W16).
//
// Address lines are driven only during write() and then released to INPUT.
// ADDR3 is not driven by demux, but IS released to INPUT to keep the bus clean.
class PlexorinoDemux {
public:
  explicit PlexorinoDemux(PlexWidth width = PlexWidth::W16);

  // Configure only demux-related pins (shared address lines are driven per-write).
  void begin();

  // Returns true once begin() has been called.
  bool begun() const;

  PlexWidth width() const;
  uint8_t count() const;   // 8 or 16 depending on width()

  // Write a single output. No-op if not begun() or addr out of range.
  void write(muxAddr_t addr, bool value) const;

  // Write multiple outputs from low bits of 'bits' (uses count() bits).
  // No-op if not begun().
  void writeBits(uint16_t bits) const;

  // Convenience: clear all outputs to 0 (manual reset; does not use 74HC259 reset pin).
  // No-op if not begun().
  void reset() const;

private:
  PlexWidth width_;
  bool begun_;
};
