#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

#define APP_PWM_FREQUENCY_HZ          20000u
#define APP_CONTROL_PERIOD_MS         1u
#define APP_CAN_TIMEOUT_MS            100u

#define APP_DUTY_STARTUP_LIMIT_PERMILLE 250u
#define APP_DUTY_MAX_PERMILLE           1000u

#define APP_OVERCURRENT_A_X1000       900
#define APP_OVERCURRENT_TIME_MS       10u
#define APP_STALL_CURRENT_A_X1000     600
#define APP_STALL_TIME_MS             150u
#define APP_UNDERVOLTAGE_V_X1000      9000
#define APP_OVERTEMP_C_X1000          80000

#define APP_ADC_COUNTS_FULL_SCALE     4095u
#define APP_ADC_REF_MV                3300u

#define APP_SHUNT_MILLIOHM            50u
#define APP_CURRENT_SENSE_GAIN        20u
#define APP_VDIV_TOP_OHM              100000u
#define APP_VDIV_BOTTOM_OHM           27000u

#define CAN_ID_MOTOR_COMMAND          0x100u
#define CAN_ID_MOTOR_STATUS           0x101u

#endif
