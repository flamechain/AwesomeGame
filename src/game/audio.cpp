#include "audio.h"

Mix_Chunk * InitializeAudio(int * Count) {
    *Count = 1;
    Mix_Chunk Chunks[1];
    Chunks[0] = *LoadWAV("resources/audio/temp.wav");
    Mix_PlayChannel(-1, &Chunks[0], 0); //-1 sets volume for all channels of audio
    return Chunks;
}

void DestroyAudio(Mix_Chunk * Chunks, int Count) {
    for (int i=0; i < Count; i++) Mix_FreeChunk(&Chunks[i]);
    Mix_CloseAudio();
}
