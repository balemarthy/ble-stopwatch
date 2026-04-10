/*
 * MODULE: oled_driver
 *
 * ROLE:
 * Provides abstracted display rendering functionality independent of hardware.
 *
 * RESPONSIBILITIES:
 * - Initialize display
 * - Clear display buffer
 * - Render text at given coordinates
 * - Update (flush) buffer to display
 *
 * OWNS:
 * - Display buffer
 * - Rendering mechanism
 *
 * DOES NOT OWN:
 * - Display content logic (ui_presenter)
 * - Application logic
 *
 * INTERACTIONS:
 * - Used by ui_presenter to render formatted data
 *
 * DESIGN NOTES:
 * - Text-based interface (sufficient for this system)
 * - Buffer-based rendering to avoid flicker
 * - Hardware-agnostic (SSD1306 handled internally later)
 *
 * ARCHITECTURE:
 * Driver Layer (hardware abstraction)
 */

#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct oled_driver oled_driver_t;

/*
 * Initialization
 */
int oled_driver_init(oled_driver_t *self);

/*
 * Clear display buffer
 */
int oled_driver_clear(oled_driver_t *self);

/*
 * Draw text at position
 */
int oled_driver_draw_text(oled_driver_t *self,
                          uint8_t x,
                          uint8_t y,
                          const char *text);

/*
 * Flush buffer to display
 */
int oled_driver_update(oled_driver_t *self);

#endif /* OLED_DRIVER_H */
