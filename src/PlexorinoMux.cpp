/*
 * PlexorinoMux.cpp
 *
 * Implements PlexorinoMux.
 *
 * Key behavior:
 *  - begin() configures only mux-related pins (and does NOT touch demux pins).
 *  - read() drives shared address lines only for the duration of the read, then
 *    releases them to high-Z (INPUT) to avoid contention with other circuitry.
 *  - Mux output is treated as inverted: return !digitalRead(PIN_MUX_DATA).
 */

#include "Plexorino.h"

// Local helpers (file scope)

static inline uint8_t widthToCount_(PlexWidth w) {
  return (w == PlexWidth::W16) ? 16 : 8;
}

static inline void driveAddrLines_(muxAddr_t addr, bool useAddr3) {
  // Shared address lines
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);

  digitalWrite(PIN_ADDR0, (addr >> 0) & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);

  // Mux-only address bit (W16)
  if (useAddr3) {
    pinMode(PIN_ADDR3, OUTPUT);
    digitalWrite(PIN_ADDR3, (addr >> 3) & 0x1);
  }
}

static inline void releaseAddrLines_(bool useAddr3) {
  // Return shared bus lines to high-Z.
  pinMode(PIN_ADDR0, INPUT);
  pinMode(PIN_ADDR1, INPUT);
  pinMode(PIN_ADDR2, INPUT);

  if (useAddr3) {
    pinMode(PIN_ADDR3, INPUT);
  }
}

// -------------------------
// PlexorinoMux
// -------------------------

PlexorinoMux::PlexorinoMux(PlexWidth width)
  : width_(width),
    begun_(false) {}

void PlexorinoMux::begin() {
  // Configure only mux pins.
  pinMode(PIN_MUX_DATA_, INPUT);

  // We deliberately do NOT set pinMode on address lines here.
  // Address lines are driven only during read() and then released to INPUT.
  // This keeps the shared bus high-Z while idle.

  begun_ = true;
}

bool PlexorinoMux::begun() const {
  return begun_;
}

PlexWidth PlexorinoMux::width() const {
  return width_;
}

uint8_t PlexorinoMux::count() const {
  return widthToCount_(width_);
}

bool PlexorinoMux::read(muxAddr_t addr) const {
  if (!begun_) return false;
  if (addr >= count()) return false;

  const bool useAddr3 = (width_ == PlexWidth::W16);

  driveAddrLines_(addr, useAddr3);

  // Read mux output (inverted by convention/wiring).
  const bool value = !digitalRead(PIN_MUX_DATA_);

  releaseAddrLines_(useAddr3);

  return value;
}
