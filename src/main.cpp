#include <GetTime.h>
#include <AnimationText.h>

const char* ssid = "loong的电子节点";
const char* password = "shijinjia";
const char* message = "Hello my dear : with a will , you can achieve anything ..........";

AnimationText animText(message, PA_SCROLL_LEFT, PA_NO_EFFECT);
GetTime timeGetter(ssid, password);

void setup() {
    animText.begin();
    timeGetter.begin();
}

void loop() {
    if (animText.loop()) {
        timeGetter.showTime(animText.getDisplay());
    }
}