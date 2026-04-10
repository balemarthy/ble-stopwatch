/*
 * MODULE: feedback_controller
 *
 * ROLE:
 * Generates user feedback patterns (e.g., buzzer signals) based on system events.
 *
 * RESPONSIBILITIES:
 * - Trigger feedback for system actions (START, LAP, RESET)
 * - Manage timing of feedback patterns
 * - Control buzzer via driver
 *
 * OWNS:
 * - Feedback pattern logic
 * - Timing state for patterns
 *
 * DOES NOT OWN:
 * - Buzzer hardware (buzzer_driver)
 * - System logic (stopwatch_core)
 *
 * INTERACTIONS:
 * - Called by stopwatch_core on user actions
 * - Uses buzzer_driver to generate sound
 *
 * DESIGN NOTES:
 * - Non-blocking (uses tick for timing)
 * - Explicit APIs for each feedback type
 * - Keeps UX behavior separate from core logic
 *
 * ARCHITECTURE:
 * Service Layer (user feedback)
 */

#ifndef FEEDBACK_CONTROLLER_H
#define FEEDBACK_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct feedback_controller feedback_controller_t;

/*
 * Initialization
 */
int feedback_controller_init(feedback_controller_t *self);

/*
 * Feedback actions
 */
int feedback_controller_beep_start(feedback_controller_t *self);

int feedback_controller_beep_lap(feedback_controller_t *self);

int feedback_controller_beep_reset(feedback_controller_t *self);

/*
 * Periodic processing (for pattern timing)
 */
void feedback_controller_tick(feedback_controller_t *self);

#endif /* FEEDBACK_CONTROLLER_H */
