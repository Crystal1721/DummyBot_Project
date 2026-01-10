#include "hipnuc_ch0x0.h"

hipnuc_raw_t hipnuc_raw;

void HIPNUC_decode_process(uint8_t* data, uint16_t len){
    char out[512];
    for (uint16_t i = 0; i < len; ++i)
    {
        uint8_t b = data[i];
        int rc = hipnuc_input(&hipnuc_raw, b);
        if (rc > 0)
        {
            int n = hipnuc_dump_packet(&hipnuc_raw, out, sizeof(out));
            if (n > 0)
            {
                // /* Use HAL UART transmit or your logging mechanism */
                // HAL_UART_Transmit(&huart4, (uint8_t*)out, n, 100);
            }
        }
    }
}
