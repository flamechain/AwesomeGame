#include "mixer.h"

GAME_START

Mix_Chunk *LoadWAV(string filename) {
    Mix_Chunk *audioFile;

    int result = Mix_OpenAudio(FREQUENCY, AUDIO_S16SYS, CHANNELS, CHUNKSIZE);

    if (result < 0) {
        ConsoleOutput("SDL mixer error: %s\n", Mix_GetError());
    }

    result = Mix_AllocateChannels(CHANNELS);

    if (result < 0) {
        ConsoleOutput("SDL mixer error: %s\n", Mix_GetError());
    }

    audioFile = Mix_LoadWAV(filename.c_str());

    if (audioFile == NULL) {
        ConsoleOutput("SDL mixer error: %s\n", Mix_GetError());
    }

    return audioFile;
}

GAME_END
