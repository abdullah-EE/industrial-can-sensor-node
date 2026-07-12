#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <stdint.h>
#include "adc_processing.h"

typedef uint32_t fault_flags_t;

enum {
    FAULT_NONE          = 0u,
    FAULT_OVERCURRENT   = 1u << 0,
    FAULT_STALL         = 1u << 1,
    FAULT_OVERTEMP      = 1u << 2,
    FAULT_UNDERVOLTAGE  = 1u << 3,
    FAULT_SENSOR        = 1u << 4,
    FAULT_CAN_TIMEOUT   = 1u << 5
};

typedef struct {
    fault_flags_t latched;
    uint32_t overcurrent_timer_ms;
    uint32_t stall_timer_ms;
} fault_manager_t;

void fault_manager_init(fault_manager_t *manager);
fault_flags_t fault_manager_update(fault_manager_t *manager,
                                   const measurements_t *measurements,
                                   uint16_t commanded_duty_per_mille,
                                   uint32_t can_age_ms,
                                   uint32_t dt_ms);
void fault_manager_clear_latched(fault_manager_t *manager, fault_flags_t clear_mask);

#endif
