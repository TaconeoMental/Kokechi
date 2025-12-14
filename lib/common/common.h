#ifndef COMMON_H
#define COMMON_H
#include <Arduino.h>

typedef struct __attribute__((packed))
{
    uint8_t magnet_present;
    uint32_t sequence;
} MagnetStatePacket;

void print_mac(const uint8_t (&mac)[6]);

#endif
