#include "audio.h"

void InitializeAudio(long long unsigned int& count, vector<Mix_Chunk>& data) {
    count = 1;
    data.resize(1);
    data[0] = *LoadWAV("resources/audio/temp.wav");
    Mix_PlayChannel(-1, &data[0], 0); //-1 sets volume for all channels of audio
}

void DestroyAudio(vector<Mix_Chunk>& data, long long unsigned int count) {
    Mix_HaltChannel(-1); // stops all channels
    DebugOutput(true, "  Halted all channels\n");

    // for (long long unsigned int i=0; i < data.size(); i++) Mix_FreeChunk(&data[i]);
    // DebugOutput(true, "  Freed all chunks\n");

    Mix_CloseAudio();
    Mix_Quit();
    DebugOutput(true, "  Closed all audio\n");
}
