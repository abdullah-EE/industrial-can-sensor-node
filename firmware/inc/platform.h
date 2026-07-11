#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include "adc_processing.h"
#include "can_protocol.h"

void platform_init(void);
uint32_t platform_millis(void);
void platform_pwm_set_duty_per_mille(uint16_t duty_per_mille);
adc_raw_t platform_adc_read_latest(void);
uint8_t platform_can_receive(can_frame_t *frame);
void platform_can_send(const can_frame_t *frame);
void platform_fault_led_set(uint8_t on);
void platform_wait_for_next_tick(void);

#endif
