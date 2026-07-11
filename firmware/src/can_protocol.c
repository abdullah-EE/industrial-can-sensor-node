#include "can_protocol.h"
#include "app_config.h"

static uint16_t read_u16_le(const uint8_t *data)
{
    return (uint16_t)data[0] | ((uint16_t)data[1] << 8);
}

static void write_u16_le(uint8_t *data, uint16_t value)
{
    data[0] = (uint8_t)(value & 0xFFu);
    data[1] = (uint8_t)(value >> 8);
}

uint8_t can_protocol_decode_command(const can_frame_t *frame, motor_command_t *command)
{
    if ((frame == 0) || (command == 0)) {
        return 0;
    }

    if ((frame->id != CAN_ID_MOTOR_COMMAND) || (frame->dlc < 3u)) {
        return 0;
    }

    command->enable = frame->data[0] ? 1u : 0u;
    command->duty_per_mille = read_u16_le(&frame->data[1]);

    if (command->duty_per_mille > APP_DUTY_MAX_PERMILLE) {
        command->duty_per_mille = APP_DUTY_MAX_PERMILLE;
    }

    return 1;
}

can_frame_t can_protocol_make_status(uint16_t applied_duty_per_mille,
                                     int32_t current_a_x1000,
                                     int32_t supply_v_x1000,
                                     fault_flags_t faults)
{
    can_frame_t frame = {0};

    frame.id = CAN_ID_MOTOR_STATUS;
    frame.dlc = 8u;
    write_u16_le(&frame.data[0], applied_duty_per_mille);
    write_u16_le(&frame.data[2], (uint16_t)current_a_x1000);
    write_u16_le(&frame.data[4], (uint16_t)supply_v_x1000);
    frame.data[6] = (uint8_t)(faults & 0xFFu);
    frame.data[7] = (uint8_t)((faults >> 8) & 0xFFu);

    return frame;
}
