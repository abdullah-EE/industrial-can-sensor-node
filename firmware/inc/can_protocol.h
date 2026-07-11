#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdint.h>
#include "fault_manager.h"

typedef struct {
    uint8_t enable;
    uint16_t duty_per_mille;
} motor_command_t;

typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
} can_frame_t;

uint8_t can_protocol_decode_command(const can_frame_t *frame, motor_command_t *command);
can_frame_t can_protocol_make_status(uint16_t applied_duty_per_mille,
                                     int32_t current_a_x1000,
                                     int32_t supply_v_x1000,
                                     fault_flags_t faults);

#endif
