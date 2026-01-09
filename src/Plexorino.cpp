/**
 * Plexorino: hardcoded-pin interface to:
 *   - 74HC259 8-output addressable latch (demultiplexer)
 *   - 74LS151 8-input multiplexer
 *   - 74LS150 16-input multiplexer
 *
 * Refactor notes:
 *   - No compile flags for 8 vs 16.
 *   - Width is selected at runtime via beginMux()/beginDemux().
 *   - Pins remain hardcoded.
 */

#include "Plexorino.h"

static PlexWidth g_muxWidth   = PlexWidth::W16;
static PlexWidth g_demuxWidth = PlexWidth::W16;
static bool g_muxBegun        = false;
static bool g_demuxBegun      = false;

static inline uint8_t widthToCount(PlexWidth w) {
  return (w == PlexWidth::W16) ? 16 : 8;
}

static inline void pulseLatch(uint8_t pin) {
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
}

void beginMux(PlexWidth width) {
  g_muxWidth = width;

  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);

  // Only touch ADDR3 if we're actually in 16-bit mux mode.
  if (g_muxWidth == PlexWidth::W16) {
    pinMode(PIN_ADDR3, OUTPUT);
  }

  pinMode(PIN_MUX_DATA_, INPUT);

  g_muxBegun = true;
}

void beginDemux(PlexWidth width) {
  g_demuxWidth = width;

  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);

  pinMode(PIN_DEMUX_DATA, OUTPUT);
  pinMode(PIN_LATCH0, OUTPUT);

  // Only touch LATCH1 if we're actually in 16-bit demux mode.
  if (g_demuxWidth == PlexWidth::W16) {
    pinMode(PIN_LATCH1, OUTPUT);
  }

  resetDemux();
  g_demuxBegun = true;
}

PlexWidth muxWidth() {
  return g_muxWidth;
}

PlexWidth demuxWidth() {
  return g_demuxWidth;
}

uint8_t muxCount() {
  return widthToCount(g_muxWidth);
}

uint8_t demuxCount() {
  return widthToCount(g_demuxWidth);
}

// Read the input at mux addr. Output from the chip comes back inverted.
bool readMux(muxAddr_t addr) {
  // Backward-compat: if user never called beginMux/setupMux, behave like old library (16-bit).
  if (!g_muxBegun) {
    beginMux(PlexWidth::W16);
  }

  if (addr >= muxCount()) {
    return false;
  }

  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);

  if (g_muxWidth == PlexWidth::W16) {
    digitalWrite(PIN_ADDR3, (addr >> 3) & 0x1);
  }

  return !digitalRead(PIN_MUX_DATA_);
}

void writeDemux(muxAddr_t addr, bool value) {
  // Backward-compat: if user never called beginDemux/setupDemux, behave like old library (16-bit).
  if (!g_demuxBegun) {
    beginDemux(PlexWidth::W16);
  }

  if (addr >= demuxCount()) {
    return;
  }

  digitalWrite(PIN_ADDR0, addr & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);

  digitalWrite(PIN_DEMUX_DATA, value);

  // Latch data onto the selected output line. Chip timings are in ns, so this is fine.
  if (g_demuxWidth == PlexWidth::W16) {
    // D0-D7 on latch0, D8-D15 on latch1
    if (addr & 0x8) {
      pulseLatch(PIN_LATCH1);
    } else {
      pulseLatch(PIN_LATCH0);
    }
  } else {
    // 8-bit demux always uses latch0
    pulseLatch(PIN_LATCH0);
  }
}

void writeBitsDemux(uint16_t bits) {
  // Ensure initialized (defaults to 16-bit for backward-compat)
  if (!g_demuxBegun) {
    beginDemux(PlexWidth::W16);
  }

  const uint8_t n = demuxCount();
  for (muxAddr_t addr = 0; addr < n; addr++) {
    writeDemux(addr, (bits >> addr) & 0x1);
  }
}

// Reset all output latches to 0
// (Note we don't use the reset pin of the chip; do it manually.)
void resetDemux() {
  // If not begun yet, we still want deterministic behavior: assume current width (default W16).
  const uint8_t n = demuxCount();
  for (muxAddr_t addr = 0; addr < n; addr++) {
    // writeDemux() will auto-begin if needed
    writeDemux(addr, false);
  }
}
