#include "platform.h"

static uint32_t fake_time_ms;
static uint16_t fake_pwm_duty;

void platform_init(void)
{
    fake_time_ms = 0u;
    fake_pwm_duty = 0u;
}

uint32_t platform_millis(void)
{
    return fake_time_ms;
}

void platform_pwm_set_duty_per_mille(uint16_t duty_per_mille)
{
    fake_pwm_duty = duty_per_mille;
    (void)fake_pwm_duty;
}

adc_raw_t platform_adc_read_latest(void)
{
    adc_raw_t raw;

    raw.current_counts = 0u;
    raw.supply_counts = 2530u;
    raw.temperature_counts = 1000u;

    return raw;
}

uint8_t platform_can_receive(can_frame_t *frame)
{
    (void)frame;
    return 0u;
}

void platform_can_send(const can_frame_t *frame)
{
    (void)frame;
}

void platform_fault_led_set(uint8_t on)
{
    (void)on;
}

void platform_wait_for_next_tick(void)
{
    fake_time_ms += 1u;
}
