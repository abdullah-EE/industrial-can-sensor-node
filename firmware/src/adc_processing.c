#include "adc_processing.h"
#include "app_config.h"

static uint8_t adc_count_valid(uint16_t counts)
{
    return counts < APP_ADC_COUNTS_FULL_SCALE;
}

measurements_t adc_processing_convert(adc_raw_t raw)
{
    measurements_t out;

    const int32_t current_mv = ((int32_t)raw.current_counts * APP_ADC_REF_MV) /
                               (int32_t)APP_ADC_COUNTS_FULL_SCALE;
    const int32_t supply_mv_at_adc = ((int32_t)raw.supply_counts * APP_ADC_REF_MV) /
                                     (int32_t)APP_ADC_COUNTS_FULL_SCALE;

    const int32_t shunt_gain_milliohm = (int32_t)APP_SHUNT_MILLIOHM *
                                        (int32_t)APP_CURRENT_SENSE_GAIN;

    out.motor_current_a_x1000 = (current_mv * 1000) / shunt_gain_milliohm;
    out.supply_voltage_v_x1000 =
        (supply_mv_at_adc * (int32_t)(APP_VDIV_TOP_OHM + APP_VDIV_BOTTOM_OHM)) /
        (int32_t)APP_VDIV_BOTTOM_OHM;

    /*
     * Placeholder temperature conversion.
     * Replace with the selected NTC or analog sensor equation before hardware validation.
     */
    out.board_temperature_c_x1000 = ((int32_t)raw.temperature_counts * 100000) /
                                    (int32_t)APP_ADC_COUNTS_FULL_SCALE;

    out.current_sensor_valid = adc_count_valid(raw.current_counts);
    out.voltage_sensor_valid = adc_count_valid(raw.supply_counts);
    out.temperature_sensor_valid = adc_count_valid(raw.temperature_counts);

    return out;
}
