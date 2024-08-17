#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <iostream>
#include <cstring>
#include <cmath>

const int AMPLITUDE = 28000;  // Amplitude of the beep sound
const int FREQUENCY = 440;    // Frequency of the beep sound (A4)

class Audio {
public:
    void init();
    void playBeep();
    void stopBeep();

private:
    SDL_AudioDeviceID audioDevice;
    bool isPlaying;
};

#endif AUDIO_H
