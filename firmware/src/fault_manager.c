#include "fault_manager.h"
#include "app_config.h"

void fault_manager_init(fault_manager_t *manager)
{
    manager->latched = FAULT_NONE;
    manager->overcurrent_timer_ms = 0u;
    manager->stall_timer_ms = 0u;
}

fault_flags_t fault_manager_update(fault_manager_t *manager,
                                   const measurements_t *measurements,
                                   uint16_t commanded_duty_per_mille,
                                   uint32_t can_age_ms,
                                   uint32_t dt_ms)
{
    fault_flags_t active = FAULT_NONE;

    if (!measurements->current_sensor_valid ||
        !measurements->voltage_sensor_valid ||
        !measurements->temperature_sensor_valid) {
        active |= FAULT_SENSOR;
    }

    if (measurements->motor_current_a_x1000 > APP_OVERCURRENT_A_X1000) {
        manager->overcurrent_timer_ms += dt_ms;
        if (manager->overcurrent_timer_ms >= APP_OVERCURRENT_TIME_MS) {
            active |= FAULT_OVERCURRENT;
        }
    } else {
        manager->overcurrent_timer_ms = 0u;
    }

    if (measurements->supply_voltage_v_x1000 < APP_UNDERVOLTAGE_V_X1000) {
        active |= FAULT_UNDERVOLTAGE;
    }

    if (measurements->board_temperature_c_x1000 > APP_OVERTEMP_C_X1000) {
        active |= FAULT_OVERTEMP;
    }

    if (can_age_ms > APP_CAN_TIMEOUT_MS) {
        active |= FAULT_CAN_TIMEOUT;
    }

    if ((commanded_duty_per_mille > 0u) &&
        (measurements->motor_current_a_x1000 > APP_STALL_CURRENT_A_X1000)) {
        manager->stall_timer_ms += dt_ms;
        if (manager->stall_timer_ms >= APP_STALL_TIME_MS) {
            active |= FAULT_STALL;
        }
    } else {
        manager->stall_timer_ms = 0u;
    }

    manager->latched |= active;
    return manager->latched;
}

void fault_manager_clear_latched(fault_manager_t *manager, fault_flags_t clear_mask)
{
    manager->latched &= ~clear_mask;
}
