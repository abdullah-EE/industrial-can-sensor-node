#ifndef ADC_PROCESSING_H
#define ADC_PROCESSING_H

#include <stdint.h>

typedef struct {
    uint16_t current_counts;
    uint16_t supply_counts;
    uint16_t temperature_counts;
} adc_raw_t;

typedef struct {
    int32_t motor_current_a_x1000;
    int32_t supply_voltage_v_x1000;
    int32_t board_temperature_c_x1000;
    uint8_t current_sensor_valid;
    uint8_t voltage_sensor_valid;
    uint8_t temperature_sensor_valid;
} measurements_t;

measurements_t adc_processing_convert(adc_raw_t raw);

#endif
