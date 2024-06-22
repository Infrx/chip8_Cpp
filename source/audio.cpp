#include "audio.h"
#include <iostream>

void audioCallback(void* userdata, Uint8* stream, int len) {
    int16_t* buffer = (int16_t*)stream; // Cast the stream to a 16-bit buffer
    int length = len / 2;               // SDL provides the length in bytes, convert to samples

    static double phase = 0.0;
    double phaseIncrement = 2.0 * M_PI * FREQUENCY / 44100.0;

    for (int i = 0; i < length; ++i) {
        buffer[i] = (int16_t)(AMPLITUDE * sin(phase));
        phase += phaseIncrement;
        if (phase >= 2.0 * M_PI) {
            phase -= 2.0 * M_PI;
        }
    }
}

void Audio::init()
{
    SDL_Init(SDL_INIT_AUDIO);
    isPlaying = false;
    SDL_AudioSpec desiredSpec;
    SDL_AudioSpec obtainedSpec;
    SDL_zero(desiredSpec);
    desiredSpec.freq = 75000;              // Sample rate (e.g., 44100 Hz)
    desiredSpec.format = AUDIO_S16SYS;     // Signed 16-bit samples in system byte order
    desiredSpec.channels = 2;              // Mono (1 channel)
    desiredSpec.samples = 4096;            // Buffer size (in samples)
    desiredSpec.callback = audioCallback;  // Callback function for audio processing
    desiredSpec.userdata = nullptr;
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &obtainedSpec, 0);
    if (audioDevice == 0) {
        std::cerr << "Failed to open audio: " << SDL_GetError() << std::endl;
    }
    else {
        std::cout << "Audio initialized successfully.\n";
    }
}

void Audio::playBeep() {
    if (!isPlaying) {
        SDL_PauseAudioDevice(audioDevice, 0); // Unpause audio
        isPlaying = true;
    }
}

void Audio::stopBeep() {
    if (isPlaying) {
        SDL_PauseAudioDevice(audioDevice, 1); // Pause audio
        isPlaying = false;
    }
}
