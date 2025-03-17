#ifndef GET_TIME_H
#define GET_TIME_H

#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

class GetTime {
public:
    GetTime(const char* ssid, const char* password);
    void begin();
    void showTime(MD_Parola& display);

private:
    const char* _ssid;
    const char* _password;
    WiFiUDP _ntpUDP;
    NTPClient _timeClient;
    char _timeStr[6];
};

#endif