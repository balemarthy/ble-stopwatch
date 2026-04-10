/*
 * MODULE: ui_presenter
 *
 * ROLE:
 * Formats and presents system data to the user via display.
 *
 * RESPONSIBILITIES:
 * - Fetch system data (time, lap info)
 * - Format data for display
 * - Control display refresh timing
 * - Send formatted output to oled_driver
 *
 * OWNS:
 * - Display formatting logic
 * - Refresh control (timing trigger)
 *
 * DOES NOT OWN:
 * - System state (stopwatch_core)
 * - Lap data (lap_recorder)
 * - Display hardware (oled_driver)
 *
 * INTERACTIONS:
 * - Pulls data from stopwatch_core and lap_recorder
 * - Uses oled_driver for rendering
 * - Triggered by periodic display update events
 *
 * DESIGN NOTES:
 * - Uses pull model (UI decides what to display)
 * - No business logic
 * - No hardware dependency
 *
 * ARCHITECTURE:
 * Service Layer (output presentation)
 */

#ifndef UI_PRESENTER_H
#define UI_PRESENTER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct ui_presenter ui_presenter_t;

/*
 * Initialization
 */
int ui_presenter_init(ui_presenter_t *self);

/*
 * Periodic update (e.g., every 50 ms)
 */
int ui_presenter_update(ui_presenter_t *self);

/*
 * Force immediate refresh
 */
int ui_presenter_force_refresh(ui_presenter_t *self);

#endif /* UI_PRESENTER_H */
