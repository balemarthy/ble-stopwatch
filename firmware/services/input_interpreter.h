/*
 * MODULE: input_interpreter
 *
 * ROLE:
 * Translates raw GPIO signals into high-level system events.
 *
 * RESPONSIBILITIES:
 * - Process button inputs
 * - Perform debounce handling
 * - Convert signals into semantic events (START/STOP, LAP, RESET)
 * - Push events to event_router
 *
 * OWNS:
 * - Button state tracking
 * - Debounce timing logic
 *
 * DOES NOT OWN:
 * - GPIO hardware (gpio_driver)
 * - Event queue (event_router)
 * - Business logic (stopwatch_core)
 *
 * INTERACTIONS:
 * - Receives input from gpio_driver (via callbacks or polling)
 * - Pushes events to event_router
 *
 * DESIGN NOTES:
 * - Separates SIGNAL from INTENT
 * - Non-blocking design
 * - Debounce handled internally using periodic tick
 *
 * ARCHITECTURE:
 * Service Layer (input handling)
 */

#ifndef INPUT_INTERPRETER_H
#define INPUT_INTERPRETER_H

#include <stdint.h>
#include <stdbool.h>

#include "event_router.h"

/*
 * Opaque type
 */
typedef struct input_interpreter input_interpreter_t;

/*
 * Button identifiers
 */
typedef enum
{
    INPUT_BUTTON_START_STOP = 0,
    INPUT_BUTTON_LAP,
    INPUT_BUTTON_RESET,

    INPUT_BUTTON_MAX
} input_button_t;

/*
 * Initialization
 */
int input_interpreter_init(input_interpreter_t *self);

/*
 * Process raw button signal
 */
int input_interpreter_process_button(input_interpreter_t *self,
                                     input_button_t button,
                                     bool pressed);

/*
 * Periodic processing (for debounce timing)
 */
void input_interpreter_tick(input_interpreter_t *self);

#endif /* INPUT_INTERPRETER_H */
