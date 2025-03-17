#ifndef ANIMATION_TEXT_H
#define ANIMATION_TEXT_H

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

class AnimationText {
public:
    AnimationText(const char* text, textEffect_t inEffect, textEffect_t outEffect);
    void begin();
    bool loop();
    MD_Parola& getDisplay();

private:
    const char* _text;
    MD_Parola _display;
    textEffect_t _inEffect;
    textEffect_t _outEffect;
};

#endif