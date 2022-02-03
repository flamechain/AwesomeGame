#include "mixer.h"

Mix_Chunk *LoadWAV(string FileName) {
    Mix_Chunk *audioFile;
//    memset(audioFile, 0, sizeof(Mix_Chunk));
    int result = Mix_OpenAudio(FREQUENCY, AUDIO_S16SYS, CHANNELS, CHUNKSIZE);

    if (result < 0) {
        ConsoleOutput("SDL mixer error: %s\n", Mix_GetError());
    }

    result = Mix_AllocateChannels(CHANNELS);

    if (result < 0) {
        ConsoleOutput("SDL mixer error: %s\n", Mix_GetError());
    }

    audioFile = Mix_LoadWAV(FileName.c_str());

    if (audioFile == NULL) {
        ConsoleOutput("SDL mixer error: %s\n", Mix_GetError());
    }
    return audioFile;
}


