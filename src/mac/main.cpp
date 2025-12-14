#include <Arduino.h>
#include <WiFi.h>


void setup()
{
    Serial.begin(115200);
    delay(1500);

    WiFi.mode(WIFI_STA);
    delay(500);
}

void loop()
{
    static bool printed = false;

    if (!printed)
    {
        int8_t mac[6];
        WiFi.macAddress(mac);
        print_mac(mac);

        printed = true;
    }

    delay(1000);
}

