/*
 * MODULE: time_base
 *
 * ROLE:
 * Provides a single, deterministic source of system time.
 *
 * RESPONSIBILITIES:
 * - Maintain elapsed time in milliseconds
 * - Start, stop, and reset time progression
 * - Provide current timestamp to other modules
 *
 * OWNS:
 * - System time (elapsed_time_ms)
 *
 * DOES NOT OWN:
 * - Timer hardware (timer_driver)
 * - Event handling
 * - Any application logic
 *
 * INTERACTIONS:
 * - Called by timer_driver via periodic tick()
 * - Queried by stopwatch_core and lap_recorder
 *
 * DESIGN NOTES:
 * - Time is monotonic and centrally owned
 * - Uses pull model (modules request time)
 * - No hardware dependency (tick is externally driven)
 * - Fully testable via simulated ticks
 *
 * ARCHITECTURE:
 * Service Layer (time management)
 */

#ifndef TIME_BASE_H
#define TIME_BASE_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type definition
 */
typedef struct time_base time_base_t;

/*
 * Initialization
 */
int time_base_init(time_base_t *self);

/*
 * Control APIs
 */
int time_base_start(time_base_t *self);

int time_base_stop(time_base_t *self);

int time_base_reset(time_base_t *self);

/*
 * Time query
 */
uint32_t time_base_get_time_ms(time_base_t *self);

/*
 * Time progression (called periodically, e.g., every 1 ms)
 */
void time_base_tick(time_base_t *self);

#endif /* TIME_BASE_H */
