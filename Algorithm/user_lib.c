#include "user_lib.h"

void ramp_init(ramp_function_source_t *ramp,
               float frame_period,
               float target_value,
               float current_value,
               float max_step_per_frame)
{
    ramp->frame_period = frame_period;
    ramp->current_value = current_value;
    ramp->target_value = target_value;
    ramp->input = max_step_per_frame; // maximum allowed increment per frame
    ramp->out = current_value;
    ramp->error = 0.0f;
}


void ramp_calc(ramp_function_source_t *ramp)
{
    ramp->error = ramp->target_value - ramp->current_value;

    float delta = ramp->error;

    // Limit the delta to maximum step
    if (delta > ramp->input)
        delta = ramp->input;
    else if (delta < -ramp->input)
        delta = -ramp->input;

    // Update current value
    ramp->current_value += delta;

    // Output for IK
    ramp->out = ramp->current_value;
}


