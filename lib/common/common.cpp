#include "common.h"
#include "mini_log.h"

void print_mac(const uint8_t (&mac)[6])
{
    MLOG_I(
        "MAC: %02X:%02X:%02X:%02X:%02X:%02X",
        mac[0], mac[1], mac[2],
        mac[3], mac[4], mac[5]
    );
}
