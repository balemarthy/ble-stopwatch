/*
 * MODULE: ble_stack_adapter
 *
 * ROLE:
 * Provides abstraction over BLE stack (e.g., Nordic SoftDevice),
 * isolating system from vendor-specific APIs.
 *
 * RESPONSIBILITIES:
 * - Initialize BLE stack
 * - Send data over BLE
 * - Translate BLE stack events into abstract events
 * - Notify upper layer via callback
 *
 * OWNS:
 * - BLE stack interaction logic
 * - Event translation mechanism
 *
 * DOES NOT OWN:
 * - Application logic (ble_gateway)
 * - Data formatting (lap data)
 *
 * INTERACTIONS:
 * - Used by ble_gateway for communication
 * - Calls registered callback on BLE events
 *
 * DESIGN NOTES:
 * - Fully decouples system from BLE SDK
 * - Uses callback mechanism for event propagation
 * - Generic send API (no application-specific data)
 *
 * ARCHITECTURE:
 * Driver Layer (hardware/SDK abstraction)
 */

#ifndef BLE_STACK_ADAPTER_H
#define BLE_STACK_ADAPTER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Opaque type
 */
typedef struct ble_stack_adapter ble_stack_adapter_t;

/*
 * BLE event types (abstracted)
 */
typedef enum
{
    BLE_ADAPTER_EVT_CONNECTED = 0,
    BLE_ADAPTER_EVT_DISCONNECTED,
    BLE_ADAPTER_EVT_TX_COMPLETE
} ble_adapter_evt_t;

/*
 * Callback type
 */
typedef void (*ble_adapter_callback_t)(ble_adapter_evt_t evt, void *context);

/*
 * Initialization
 */
int ble_stack_adapter_init(ble_stack_adapter_t *self);

/*
 * Register callback for BLE events
 */
int ble_stack_adapter_register_callback(ble_stack_adapter_t *self,
                                        ble_adapter_callback_t callback,
                                        void *context);

/*
 * Send data
 */
int ble_stack_adapter_send(ble_stack_adapter_t *self,
                           const uint8_t *data,
                           uint16_t length);

/*
 * Process BLE stack events
 */
int ble_stack_adapter_process(ble_stack_adapter_t *self);

#endif /* BLE_STACK_ADAPTER_H */
