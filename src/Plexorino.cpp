/**
 * Plexorino.cpp
 *
 * Interface to:
 *   - 74HC259 8-output addressable latch (demux) x1 or x2 (8 or 16 outputs)
 *   - 74LS151 8-input mux
 *   - 74LS150 16-input mux
 *
 * Design principles (per refactor):
 *   - No compile-time width flags.
 *   - Width is selected at runtime via beginMux()/beginDemux().
 *   - beginDemux() / beginMux() ONLY configure pins and state; they do NOT reset/clear outputs.
 *   - writeDemux() ONLY writes a single output (no hidden reset, no auto-init).
 *   - If the user forgets to call beginMux/beginDemux, operations become no-ops / return false.
 */

#include "Plexorino.h"

// -------------------------
// Module state
// -------------------------

static PlexWidth g_muxWidth = PlexWidth::W16;
static PlexWidth g_demuxWidth = PlexWidth::W16;

static bool g_muxBegun = false;
static bool g_demuxBegun = false;

static inline uint8_t widthToCount_(PlexWidth w)
{
  return (w == PlexWidth::W16) ? 16 : 8;
}

static inline void pulseLatch_(uint8_t pin)
{
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
}

// -------------------------
// Public: width + counts
// -------------------------

PlexWidth muxWidth()
{
  return g_muxWidth;
}

PlexWidth demuxWidth()
{
  return g_demuxWidth;
}

uint8_t muxCount()
{
  return widthToCount_(g_muxWidth);
}

uint8_t demuxCount()
{
  return widthToCount_(g_demuxWidth);
}

// -------------------------
// Public: initialization
// -------------------------

void beginMux(PlexWidth width)
{
  g_muxWidth = width;

  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);

  // Only touch ADDR3 when in W16 mode. In W8 mode we leave it alone.
  if (g_muxWidth == PlexWidth::W16)
  {
    pinMode(PIN_ADDR3, OUTPUT);
  }

  pinMode(PIN_MUX_DATA_, INPUT);

  g_muxBegun = true;
}

void beginDemux(PlexWidth width)
{
  g_demuxWidth = width;

  pinMode(PIN_ADDR0, OUTPUT);
  pinMode(PIN_ADDR1, OUTPUT);
  pinMode(PIN_ADDR2, OUTPUT);

  pinMode(PIN_DEMUX_DATA, OUTPUT);
  pinMode(PIN_LATCH0, OUTPUT);

  // Only touch LATCH1 when in W16 mode. In W8 mode we leave it alone.
  if (g_demuxWidth == PlexWidth::W16)
  {
    pinMode(PIN_LATCH1, OUTPUT);
  }

  g_demuxBegun = true;
}

// -------------------------
// Public: mux read
// -------------------------

bool readMux(muxAddr_t addr)
{
  if (!g_muxBegun)
    return false;
  if (addr >= muxCount())
    return false;

  digitalWrite(PIN_ADDR0, (addr >> 0) & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);

  if (g_muxWidth == PlexWidth::W16)
  {
    digitalWrite(PIN_ADDR3, (addr >> 3) & 0x1);
  }

  // Output from mux is inverted in Plexorino wiring convention.
  return !digitalRead(PIN_MUX_DATA_);
}

// -------------------------
// Public: demux write
// -------------------------

void writeDemux(muxAddr_t addr, bool value)
{
  if (!g_demuxBegun)
    return;
  if (addr >= demuxCount())
    return;

  digitalWrite(PIN_ADDR0, (addr >> 0) & 0x1);
  digitalWrite(PIN_ADDR1, (addr >> 1) & 0x1);
  digitalWrite(PIN_ADDR2, (addr >> 2) & 0x1);

  digitalWrite(PIN_DEMUX_DATA, value);

  // Latch onto the selected output line.
  // Chip timings are in ns; digitalWrite() pulses are plenty.
  if (g_demuxWidth == PlexWidth::W16)
  {
    if (addr & 0x8)
      pulseLatch_(PIN_LATCH1); // outputs 8–15
    else
      pulseLatch_(PIN_LATCH0); // outputs 0–7
  }
  else
  {
    pulseLatch_(PIN_LATCH0); // outputs 0–7
  }
}

void writeBitsDemux(uint16_t bits)
{
  if (!g_demuxBegun)
    return;

  const uint8_t n = demuxCount();
  for (muxAddr_t addr = 0; addr < n; addr++)
  {
    writeDemux(addr, (bits >> addr) & 0x1);
  }
}

void resetDemux()
{
  // Manual reset (we do not use the 74HC259 reset pin).
  // No-op if beginDemux() has not been called.
  writeBitsDemux(0);
}
