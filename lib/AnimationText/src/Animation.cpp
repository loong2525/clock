#include "AnimationText.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CS_PIN 5
#define MAX_DEVICES 4

AnimationText::AnimationText(const char* text, textEffect_t inEffect, textEffect_t outEffect)
    : _text(text), _display(HARDWARE_TYPE, CS_PIN, MAX_DEVICES), _inEffect(inEffect), _outEffect(outEffect) {}

void AnimationText::begin() {
    if (!_display.begin()) {
        while (1);
    }
    _display.setIntensity(15);
    _display.setTextEffect(_inEffect, _outEffect);
    _display.setTextAlignment(PA_LEFT);
    _display.setSpeed(200);
    _display.setPause(1000);
    _display.displayText(_text, PA_LEFT, 100, 1000, _inEffect, _outEffect);
}

bool AnimationText::loop() {
    if (_display.displayAnimate()) {
        _display.displayReset();
        return true;
    }
    return false;
}

MD_Parola& AnimationText::getDisplay() {
    return _display;
}