#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>
#include "fault_manager.h"

typedef struct {
    uint16_t requested_duty_per_mille;
    uint16_t applied_duty_per_mille;
    uint16_t duty_limit_per_mille;
    uint8_t enabled;
} motor_control_t;

void motor_control_init(motor_control_t *motor);
void motor_control_set_command(motor_control_t *motor, uint8_t enable, uint16_t duty_per_mille);
void motor_control_apply(motor_control_t *motor, fault_flags_t faults);

#endif
