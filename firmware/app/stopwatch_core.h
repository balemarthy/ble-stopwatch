/*
 * MODULE: stopwatch_core
 *
 * ROLE:
 * Central application logic of the stopwatch system.
 *
 * RESPONSIBILITIES:
 * - Maintain stopwatch state (STOPPED, RUNNING, PAUSED)
 * - Process high-level user events (START/STOP, LAP, RESET)
 * - Coordinate system behavior across modules
 *
 * OWNS:
 * - System state
 *
 * DOES NOT OWN:
 * - Time measurement (time_base)
 * - Lap storage (lap_recorder)
 * - Hardware interaction (drivers)
 *
 * INTERACTIONS:
 * - Receives events from event_router
 * - Uses time_base, lap_recorder
 * - Triggers UI, BLE, and feedback modules
 *
 * DESIGN NOTES:
 * - Pure logic (no hardware dependency)
 * - Event-driven interface (handle_event)
 * - Fully testable in isolation
 *
 * ARCHITECTURE:
 * Application Layer (core domain logic)
 */
#ifndef STOPWATCH_CORE_H
#define STOPWATCH_CORE_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type definition
 */
typedef struct stopwatch_core stopwatch_core_t;

/*
 * Stopwatch states
 */
typedef enum
{
    STOPWATCH_STATE_STOPPED = 0,
    STOPWATCH_STATE_RUNNING,
    STOPWATCH_STATE_PAUSED
} stopwatch_state_t;

/*
 * Events handled by stopwatch core
 */
typedef enum
{
    STOPWATCH_EVENT_START_STOP = 0,
    STOPWATCH_EVENT_LAP,
    STOPWATCH_EVENT_RESET
} stopwatch_event_t;

/*
 * Initialization
 */
int stopwatch_core_init(stopwatch_core_t *self);

/*
 * Event processing (PRIMARY API)
 */
int stopwatch_core_handle_event(stopwatch_core_t *self,
                                 stopwatch_event_t event);

/*
 * Query APIs
 */
stopwatch_state_t stopwatch_core_get_state(stopwatch_core_t *self);

uint32_t stopwatch_core_get_elapsed_time(stopwatch_core_t *self);

uint8_t stopwatch_core_get_lap_count(stopwatch_core_t *self);

uint32_t stopwatch_core_get_last_lap(stopwatch_core_t *self);

#endif /* STOPWATCH_CORE_H */
