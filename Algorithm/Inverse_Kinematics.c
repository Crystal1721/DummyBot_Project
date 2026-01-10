#include "Inverse_Kinematics.h"
#include "math.h"

void InverseKinematics (RRR_Bot_t * Dummy_bot) {

    float x_4, y_4, z_4, z_1, z_1_4, xy_4, v_side, q2_a, q2_b;

    x_4 = 0.0f;
    y_4 = 0.0f;
    z_4 = 0.0f;

    // Find the value for the fist angle
    Dummy_bot->current_q1 = atan2f(Dummy_bot->y_EE, Dummy_bot->x_EE);

    // Find the values for the position of joint #4 for x, y, z
    x_4 = Dummy_bot->x_EE - (Dummy_bot->L4 * cosf(Dummy_bot->current_q1));
    y_4 = Dummy_bot->y_EE - (Dummy_bot->L4 * sinf(Dummy_bot->current_q1));
    z_4 = Dummy_bot->z_EE;

    // Find the length of the third side of the (virtual) triangle made by L2,
    // L3 in the vertical plane of the robot arm

    // Specify the z poisition of joint #1
    z_1 = Dummy_bot->L1;

    // First we find the z distance between joint #1 and joint #4 (in the world frame)
    z_1_4 = z_4 - z_1;

    // Find the true distance (in x, y plane) to joint #4
    xy_4 = sqrtf((x_4 * x_4) + (y_4 * y_4));

    //  Then we find the length of the virtual side made by the right angle triangle
    v_side = sqrtf((z_1_4 * z_1_4) + (xy_4 * xy_4));

    // Find the value for the angle at joint #3

    Dummy_bot->current_q3 = - (M_PI - acosf((Dummy_bot->L2 * Dummy_bot->L2 + Dummy_bot->L3 * Dummy_bot->L3 - v_side * v_side) / (2 * Dummy_bot->L2 * Dummy_bot->L3)));

    // Find the value for the angle at joint #2 %DEBUG HERE4
    // Find the value of the angle from the x-y plane to the virtual side

    q2_a = atan2f(z_1_4, xy_4);

    q2_b = acosf((v_side * v_side + Dummy_bot->L2 * Dummy_bot->L2 - Dummy_bot->L3 * Dummy_bot->L3) / (2 * v_side * Dummy_bot->L2));

    Dummy_bot->current_q2 = q2_a + q2_b;


    Dummy_bot->current_q1 = Dummy_bot->current_q1 * 180.0f/M_PI;
    Dummy_bot->current_q2 = Dummy_bot->current_q2 * 180.0f/M_PI;
    Dummy_bot->current_q3 = Dummy_bot->current_q3 * 180.0f/M_PI;

}
