#include "motor_control.h"
#include "app_config.h"
#include "platform.h"

static uint16_t clamp_duty(uint16_t duty, uint16_t limit)
{
    if (duty > limit) {
        return limit;
    }
    return duty;
}

void motor_control_init(motor_control_t *motor)
{
    motor->requested_duty_per_mille = 0u;
    motor->applied_duty_per_mille = 0u;
    motor->duty_limit_per_mille = APP_DUTY_STARTUP_LIMIT_PERMILLE;
    motor->enabled = 0u;
    platform_pwm_set_duty_per_mille(0u);
}

void motor_control_set_command(motor_control_t *motor, uint8_t enable, uint16_t duty_per_mille)
{
    motor->enabled = enable ? 1u : 0u;
    motor->requested_duty_per_mille = clamp_duty(duty_per_mille, APP_DUTY_MAX_PERMILLE);
}

void motor_control_apply(motor_control_t *motor, fault_flags_t faults)
{
    if (!motor->enabled || (faults != FAULT_NONE)) {
        motor->applied_duty_per_mille = 0u;
    } else {
        motor->applied_duty_per_mille =
            clamp_duty(motor->requested_duty_per_mille, motor->duty_limit_per_mille);
    }

    platform_pwm_set_duty_per_mille(motor->applied_duty_per_mille);
}
