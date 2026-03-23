#ifndef USER_LIB_H
#define USER_LIB_H

#include "stdint.h"

typedef struct {
    float frame_period;   // loop period (s)
    float current_value;  // current position / angle
    float target_value;   // target position / angle
    float input;          // maximum step per frame
    float out;            // output value for IK
    float error;          // target - current
} ramp_function_source_t;

extern ramp_function_source_t ramp_q1, ramp_q2, ramp_q3;

void ramp_init(ramp_function_source_t *ramp,
               float frame_period,
               float target_value,
               float current_value,
               float max_step_per_frame);

void ramp_calc(ramp_function_source_t *ramp);

#endif /* USER_LIB_H */

