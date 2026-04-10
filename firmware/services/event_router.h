/*
 * MODULE: event_router
 *
 * ROLE:
 * Provides a central event queue for decoupled communication between modules.
 *
 * RESPONSIBILITIES:
 * - Store events in FIFO order
 * - Allow producers to push events
 * - Allow main loop to pop events
 * - Maintain queue integrity (no overflow corruption)
 *
 * OWNS:
 * - Event queue (ring buffer)
 * - Head and tail indices
 *
 * DOES NOT OWN:
 * - Event handling logic
 * - Business decisions
 * - Any module-specific behavior
 *
 * INTERACTIONS:
 * - Producers: input_interpreter, time_base, ble_gateway
 * - Consumer: main loop dispatcher
 *
 * DESIGN NOTES:
 * - Implements message queue pattern
 * - ISR-safe push operation
 * - No dynamic memory
 * - Router does NOT dispatch events (only transports)
 *
 * ARCHITECTURE:
 * Service Layer (event infrastructure)
 */

#ifndef EVENT_ROUTER_H
#define EVENT_ROUTER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Configuration
 */
#define EVENT_ROUTER_MAX_EVENTS   (32U)

/*
 * Event Types (System-wide)
 */
typedef enum
{
    EVENT_NONE = 0,

    /* Input Events */
    EVENT_START_STOP,
    EVENT_LAP,
    EVENT_RESET,

    /* System Events */
    EVENT_TIMER_TICK,
    EVENT_DISPLAY_UPDATE,

    /* BLE Events */
    EVENT_BLE_CONNECTED,
    EVENT_BLE_DISCONNECTED,
    EVENT_BLE_TX_COMPLETE

} event_type_t;

/*
 * Event Object
 */
typedef struct
{
    event_type_t type;
    uint32_t data;   /* Optional payload */
} event_t;

/*
 * Opaque type
 */
typedef struct event_router event_router_t;

/*
 * Initialization
 */
int event_router_init(event_router_t *self);

/*
 * Push event (called by producers, including ISR)
 */
bool event_router_push(event_router_t *self, const event_t *event);

/*
 * Pop event (called by main loop)
 */
bool event_router_pop(event_router_t *self, event_t *event);

/*
 * Utility APIs
 */
bool event_router_is_empty(event_router_t *self);

bool event_router_is_full(event_router_t *self);

#endif /* EVENT_ROUTER_H */
