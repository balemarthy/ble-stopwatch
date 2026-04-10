/*
 * MODULE: timer_driver
 *
 * ROLE:
 * Provides generic periodic timer functionality independent of hardware.
 *
 * RESPONSIBILITIES:
 * - Configure and start periodic timer
 * - Invoke callback on timer expiry
 * - Stop timer operation
 *
 * OWNS:
 * - Timer configuration state
 * - Callback registration
 *
 * DOES NOT OWN:
 * - Time tracking (time_base)
 * - Application logic
 * - Event handling
 *
 * INTERACTIONS:
 * - Calls registered callback (e.g., time_base_tick)
 * - Used by system to generate periodic ticks
 *
 * DESIGN NOTES:
 * - Callback-based design (decoupled)
 * - No knowledge of system modules
 * - Non-blocking, interrupt-driven
 *
 * ARCHITECTURE:
 * Driver Layer (hardware abstraction)
 */

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct timer_driver timer_driver_t;

/*
 * Timer callback type
 */
typedef void (*timer_callback_t)(void *context);

/*
 * Initialization
 */
int timer_driver_init(timer_driver_t *self);

/*
 * Start periodic timer
 */
int timer_driver_start(timer_driver_t *self,
                       uint32_t period_ms,
                       timer_callback_t callback,
                       void *context);

/*
 * Stop timer
 */
int timer_driver_stop(timer_driver_t *self);

#endif /* TIMER_DRIVER_H */
