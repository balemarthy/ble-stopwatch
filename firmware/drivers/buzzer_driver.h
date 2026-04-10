/*
 * MODULE: buzzer_driver
 *
 * ROLE:
 * Provides abstracted sound generation capability using hardware (e.g., PWM).
 *
 * RESPONSIBILITIES:
 * - Initialize buzzer hardware
 * - Start sound generation with given frequency and duty cycle
 * - Stop sound generation
 *
 * OWNS:
 * - Buzzer control state
 *
 * DOES NOT OWN:
 * - Feedback patterns (feedback_controller)
 * - Application logic
 *
 * INTERACTIONS:
 * - Used by feedback_controller to generate sound
 *
 * DESIGN NOTES:
 * - Supports PWM-based tone generation
 * - Non-blocking operation
 * - Hardware-agnostic interface
 *
 * ARCHITECTURE:
 * Driver Layer (hardware abstraction)
 */

#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct buzzer_driver buzzer_driver_t;

/*
 * Initialization
 */
int buzzer_driver_init(buzzer_driver_t *self);

/*
 * Start buzzer with frequency (Hz) and duty cycle (%)
 */
int buzzer_driver_start(buzzer_driver_t *self,
                        uint32_t frequency_hz,
                        uint8_t duty_cycle_percent);

/*
 * Stop buzzer
 */
int buzzer_driver_stop(buzzer_driver_t *self);

#endif /* BUZZER_DRIVER_H */
