/*
 * MODULE: gpio_driver
 *
 * ROLE:
 * Provides generic digital I/O access independent of hardware platform.
 *
 * RESPONSIBILITIES:
 * - Configure GPIO pins (input/output)
 * - Read pin state
 * - Write pin state
 * - Provide interrupt/callback mechanism
 *
 * OWNS:
 * - GPIO configuration state (per pin)
 *
 * DOES NOT OWN:
 * - Button semantics (input_interpreter)
 * - Application logic
 * - Hardware-specific meaning of pins
 *
 * INTERACTIONS:
 * - Used by input_interpreter for button handling
 * - Used by other modules for digital I/O
 *
 * DESIGN NOTES:
 * - Hardware-agnostic interface
 * - Supports both polling and interrupt modes
 * - Reports signal, not meaning
 *
 * ARCHITECTURE:
 * Driver Layer (hardware abstraction)
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct gpio_driver gpio_driver_t;

/*
 * GPIO direction
 */
typedef enum
{
    GPIO_DIR_INPUT = 0,
    GPIO_DIR_OUTPUT
} gpio_direction_t;

/*
 * GPIO pull configuration
 */
typedef enum
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} gpio_pull_t;

/*
 * GPIO edge type (for interrupts)
 */
typedef enum
{
    GPIO_EDGE_NONE = 0,
    GPIO_EDGE_RISING,
    GPIO_EDGE_FALLING,
    GPIO_EDGE_BOTH
} gpio_edge_t;

/*
 * Callback type
 */
typedef void (*gpio_callback_t)(uint8_t pin, void *context);

/*
 * Initialization
 */
int gpio_driver_init(gpio_driver_t *self);

/*
 * Configure a GPIO pin
 */
int gpio_configure(gpio_driver_t *self,
                   uint8_t pin,
                   gpio_direction_t direction,
                   gpio_pull_t pull);

/*
 * Read GPIO pin
 */
bool gpio_read(gpio_driver_t *self, uint8_t pin);

/*
 * Write GPIO pin
 */
int gpio_write(gpio_driver_t *self, uint8_t pin, bool value);

/*
 * Register interrupt callback
 */
int gpio_register_callback(gpio_driver_t *self,
                           uint8_t pin,
                           gpio_edge_t edge,
                           gpio_callback_t callback,
                           void *context);

#endif /* GPIO_DRIVER_H */
