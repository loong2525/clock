#include "GetTime.h"

GetTime::GetTime(const char* ssid, const char* password)
    : _ssid(ssid), _password(password), _timeClient(_ntpUDP, "ntp.aliyun.com", 28800, 60000) {}

void GetTime::begin() {
    Serial.begin(115200);
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    _timeClient.begin();
}

void GetTime::showTime(MD_Parola& display) {
    if (_timeClient.update()) {
        int hours = _timeClient.getHours();
        int minutes = _timeClient.getMinutes();
        sprintf(_timeStr, " %02d:%02d ", hours, minutes);
        display.displayText(_timeStr, PA_LEFT, 100, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
        while (display.displayAnimate());
    }
}