/*
 * MODULE: ble_gateway
 *
 * ROLE:
 * Handles system-level BLE communication and isolates application logic
 * from BLE stack details.
 *
 * RESPONSIBILITIES:
 * - Manage BLE connection state
 * - Send lap data over BLE
 * - Process BLE events from adapter layer
 *
 * OWNS:
 * - BLE connection state
 *
 * DOES NOT OWN:
 * - BLE stack implementation (ble_stack_adapter)
 * - Lap data storage (lap_recorder)
 * - Application logic (stopwatch_core)
 *
 * INTERACTIONS:
 * - Called by stopwatch_core to send lap data
 * - Uses ble_stack_adapter for communication
 * - Receives events via ble_stack_adapter callbacks
 *
 * DESIGN NOTES:
 * - Fully asynchronous (non-blocking)
 * - Safe under disconnect conditions
 * - No BLE stack types exposed
 *
 * ARCHITECTURE:
 * Service Layer (communication boundary)
 */

#ifndef BLE_GATEWAY_H
#define BLE_GATEWAY_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct ble_gateway ble_gateway_t;

/*
 * BLE connection state
 */
typedef enum
{
    BLE_STATE_DISCONNECTED = 0,
    BLE_STATE_CONNECTED
} ble_state_t;

/*
 * Initialization
 */
int ble_gateway_init(ble_gateway_t *self);

/*
 * Process BLE events (from adapter)
 */
int ble_gateway_process_event(ble_gateway_t *self,
                             uint32_t ble_evt_id,
                             void *ble_evt_data);

/*
 * Send lap data
 */
int ble_gateway_send_lap(ble_gateway_t *self,
                         uint8_t lap_index,
                         uint32_t lap_time_ms,
                         uint32_t total_time_ms);

/*
 * Query APIs
 */
ble_state_t ble_gateway_get_state(ble_gateway_t *self);

bool ble_gateway_is_connected(ble_gateway_t *self);

#endif /* BLE_GATEWAY_H */
