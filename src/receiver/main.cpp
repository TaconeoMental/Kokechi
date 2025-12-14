#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "common.h"
#include "mini_log.h"


static const int MOTOR_PIN = 5;

static bool magnetPresent = false;
static bool vibrating = false;

void vibrate()
{
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(MOTOR_PIN, HIGH);
        delay(200);
        digitalWrite(MOTOR_PIN, LOW);
        delay(300);
    }
}

void on_receive(
    const uint8_t *mac,
    const uint8_t *data,
    int len
)
{
    if (len != (int)sizeof(MagnetStatePacket))
    {
        return;
    }

    MagnetStatePacket packet;
    memcpy(&packet, data, sizeof(MagnetStatePacket));

    if (packet.magnet_present == 1 && magnetPresent == false)
    {
        magnetPresent = true;
        vibrate();
    }
    else if (packet.magnet_present == 0)
    {
        magnetPresent = false;
    }
}

void setup()
{
    uint8_t mac[6];

    LOGGER_INIT();

    pinMode(MOTOR_PIN, OUTPUT);
    digitalWrite(MOTOR_PIN, LOW);

    WiFi.mode(WIFI_STA);

    delay(5000);

    WiFi.macAddress(mac);
    print_mac(mac);

    if (esp_now_init() != ESP_OK)
    {
        MLOG_E("ESP-NOW init fail");
        return;
    }

    esp_now_register_recv_cb(on_receive);
    MLOG_T("Receiver callback set");

    MLOG_I("Receiver ready");
}

void loop()
{
}

