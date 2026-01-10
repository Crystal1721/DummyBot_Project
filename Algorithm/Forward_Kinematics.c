#include "Forward_Kinematics.h"
#include "math.h"

void Forward_Kinematics (RRR_Bot_t * Dummy_bot) {

    Dummy_bot->temp_current_q1 = (Dummy_bot->current_q1 / 180.0f) * M_PI;
    Dummy_bot->temp_current_q2 = (Dummy_bot->current_q2 / 180.0f) * M_PI;
    Dummy_bot->temp_current_q3 = (Dummy_bot->current_q3 / 180.0f) * M_PI;

    Dummy_bot->x_EE_FK = cosf(Dummy_bot->temp_current_q1) * (cosf(Dummy_bot->temp_current_q2 + Dummy_bot->temp_current_q3) * Dummy_bot->L3 + cosf(Dummy_bot->temp_current_q2) * Dummy_bot->L2) + (Dummy_bot->L4 * cosf(Dummy_bot->temp_current_q1));

    Dummy_bot->y_EE_FK = sinf(Dummy_bot->temp_current_q1) * (cosf(Dummy_bot->temp_current_q2 + Dummy_bot->temp_current_q3) * Dummy_bot->L3 + cosf(Dummy_bot->temp_current_q2) * Dummy_bot->L2) + (Dummy_bot->L4 * sinf(Dummy_bot->temp_current_q1));

    Dummy_bot->z_EE_FK = Dummy_bot->L1 + (sinf(Dummy_bot->temp_current_q2) * Dummy_bot->L2) + sinf(Dummy_bot->temp_current_q2 + Dummy_bot->temp_current_q3) * Dummy_bot->L3;

}
