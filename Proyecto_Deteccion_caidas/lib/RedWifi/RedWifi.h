#include <Arduino.h>
#include <WiFi.h>
#include <Variables.h>

class RedWifi
{
    public:
    RedWifi();
    void conectar();

    private:
    const char* _ssid;
    const char* _password;
};