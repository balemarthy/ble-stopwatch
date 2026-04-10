/*
 * MODULE: lap_recorder
 *
 * ROLE:
 * Manages lap data storage and duration calculation.
 *
 * RESPONSIBILITIES:
 * - Record lap timestamps
 * - Compute lap durations
 * - Maintain lap history (fixed size)
 * - Provide lap data to other modules
 *
 * OWNS:
 * - Lap storage (array of lap times)
 * - Lap count
 * - Previous timestamp for delta calculation
 *
 * DOES NOT OWN:
 * - System time (time_base)
 * - System state (stopwatch_core)
 * - Any hardware interaction
 *
 * INTERACTIONS:
 * - Called by stopwatch_core on LAP event
 * - Uses timestamps provided by time_base
 * - Queried by ui_presenter and ble_gateway
 *
 * DESIGN NOTES:
 * - Fixed-size storage (no dynamic memory)
 * - Time is injected (no dependency on time_base)
 * - Deterministic and testable
 *
 * ARCHITECTURE:
 * Application Layer (data management)
 */

#ifndef LAP_RECORDER_H
#define LAP_RECORDER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Configuration
 */
#define LAP_RECORDER_MAX_LAPS   (32U)

/*
 * Opaque type definition
 */
typedef struct lap_recorder lap_recorder_t;

/*
 * Initialization
 */
int lap_recorder_init(lap_recorder_t *self);

/*
 * Reset all lap data
 */
int lap_recorder_reset(lap_recorder_t *self);

/*
 * Record a lap using current timestamp
 */
int lap_recorder_record(lap_recorder_t *self, uint32_t current_time_ms);

/*
 * Query APIs
 */
uint8_t lap_recorder_get_count(lap_recorder_t *self);

uint32_t lap_recorder_get_last_lap(lap_recorder_t *self);

uint32_t lap_recorder_get_lap(lap_recorder_t *self, uint8_t index);

#endif /* LAP_RECORDER_H */
