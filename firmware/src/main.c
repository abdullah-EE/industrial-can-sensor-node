#include "adc_processing.h"
#include "app_config.h"
#include "can_protocol.h"
#include "fault_manager.h"
#include "motor_control.h"
#include "platform.h"

int main(void)
{
    motor_control_t motor;
    fault_manager_t fault_manager;
    motor_command_t command = {0};
    uint32_t last_command_ms = 0u;
    uint32_t last_status_ms = 0u;

    platform_init();
    motor_control_init(&motor);
    fault_manager_init(&fault_manager);

    for (;;) {
        const uint32_t now_ms = platform_millis();
        can_frame_t rx;

        while (platform_can_receive(&rx)) {
            if (can_protocol_decode_command(&rx, &command)) {
                motor_control_set_command(&motor, command.enable, command.duty_per_mille);
                last_command_ms = now_ms;
            }
        }

        const adc_raw_t raw = platform_adc_read_latest();
        const measurements_t measurements = adc_processing_convert(raw);
        const uint32_t can_age_ms = now_ms - last_command_ms;

        const fault_flags_t faults = fault_manager_update(&fault_manager,
                                                          &measurements,
                                                          motor.requested_duty_per_mille,
                                                          can_age_ms,
                                                          APP_CONTROL_PERIOD_MS);

        motor_control_apply(&motor, faults);
        platform_fault_led_set(faults != FAULT_NONE);

        if ((now_ms - last_status_ms) >= 100u) {
            const can_frame_t status = can_protocol_make_status(motor.applied_duty_per_mille,
                                                               measurements.motor_current_a_x1000,
                                                               measurements.supply_voltage_v_x1000,
                                                               faults);
            platform_can_send(&status);
            last_status_ms = now_ms;
        }

        platform_wait_for_next_tick();
    }
}
