#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <mini_log.h>

// CONFIG //

static const int REED_PIN = 5;

uint8_t receiverMac[] = { 0x10, 0x00, 0x3B, 0xAE, 0xD3, 0xA8 };

static bool lastMagnet = false;
static uint32_t seq = 0;

void on_send_complete(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    MLOG_D("Send: %s", status == ESP_NOW_SEND_SUCCESS ? "ok" : "fail");
}

void send_magnet(bool present)
{
    Msg msg;

    msg.magnet = present ? 1 : 0;
    msg.seq    = seq++;

    esp_err_t result = esp_now_send(
        receiverMac,
        (uint8_t *)&msg,
        sizeof(msg)
    );

    if (result != ESP_OK)
    {
        MLOG_E("Send error");
    }
}

void setup()
{
    LOGGER_INIT();

    pinMode(REED_PIN, INPUT_PULLUP);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        MLOG_E("ESP-NOW init fail");
        return;
    }

    esp_now_register_send_cb(on_send_complete);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        MLOG_E("Add peer fail");
    }

    MLOG_I("Bag ready")
}

void loop()
{
    bool present = (digitalRead(REED_PIN) == LOW);

    if (present != lastMagnet)
    {
        send_magnet(present);
        lastMagnet = present;
    }

    delay(50);
}

