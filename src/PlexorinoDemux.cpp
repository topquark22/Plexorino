/*
 * PlexorinoDemux.cpp
 *
 * Implements PlexorinoDemux.
 *
 * Key behavior:
 *  - begin() configures only demux-related pins (and does NOT touch mux pins).
 *  - write() drives shared address lines only for the duration of the write, then
 *    releases them to high-Z (INPUT) to avoid contention with other circuitry.
 *  - reset() is a convenience helper that clears outputs by calling write() for
 *    each address; it does NOT use the 74HC259 reset pin.
 *
 * Address-bus note:
 *  - Demux uses only ADDR0..ADDR2.
 *  - We also release ADDR3 to INPUT when done to be a good bus citizen, since
 *    another subsystem (or user code) might have previously driven it.
 */

#include "Plexorino.h"

// Local helpers (file scope)

static inline uint8_t widthToCount_(PlexWidth w) {
  return (w == PlexWidth::W16) ? 16 : 8;
}

static inline void pulseLatch_(uint8_t pin) {
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
}

static inline void driveAddrLines_(muxAddr_t addr) {
  // Shared address lines (demux uses only ADDR0..ADDR2)
  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);

  digitalWrite(PIN_ADDR0, (addr >> 0) & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);
}

static inline void releaseAddrLines_() {
  // Return shared bus lines to high-Z.
  pinMode(PIN_ADDR0, INPUT);
  pinMode(PIN_ADDR1, INPUT);
  pinMode(PIN_ADDR2, INPUT);
}

// -------------------------
// PlexorinoDemux
// -------------------------

PlexorinoDemux::PlexorinoDemux(PlexWidth width)
  : width_(width),
    begun_(false) {}

void PlexorinoDemux::begin() {
  // Configure only demux pins.
  pinMode(PIN_DEMUX_DATA, OUTPUT);
  pinMode(PIN_LATCH0, OUTPUT);

  if (width_ == PlexWidth::W16) {
    pinMode(PIN_LATCH1, OUTPUT);
  }

  // We deliberately do NOT set pinMode on address lines here.
  // Address lines are driven only during write() and then released to INPUT.
  // This keeps the shared bus high-Z while idle.

  begun_ = true;
}

bool PlexorinoDemux::begun() const {
  return begun_;
}

PlexWidth PlexorinoDemux::width() const {
  return width_;
}

uint8_t PlexorinoDemux::count() const {
  return widthToCount_(width_);
}

void PlexorinoDemux::write(muxAddr_t addr, bool value) const {
  if (!begun_) return;
  if (addr >= count()) return;

  driveAddrLines_(addr);

  digitalWrite(PIN_DEMUX_DATA, value);

  // Latch onto the selected output line.
  // In W16 mode, addr bit 3 selects which 74HC259 to latch.
  if (width_ == PlexWidth::W16) {
    if (addr & 0x8) pulseLatch_(PIN_LATCH1);  // outputs 8–15
    else            pulseLatch_(PIN_LATCH0);  // outputs 0–7
  } else {
    pulseLatch_(PIN_LATCH0);                  // outputs 0–7
  }

  releaseAddrLines_();
}

void PlexorinoDemux::writeBits(uint16_t bits) const {
  if (!begun_) return;

  const uint8_t n = count();
  for (muxAddr_t addr = 0; addr < n; addr++) {
    write(addr, (bits >> addr) & 0x1);
  }
}

void PlexorinoDemux::reset() const {
  if (!begun_) return;
  writeBits(0);
}

