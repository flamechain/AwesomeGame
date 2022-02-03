#ifndef AUDIO_H
#define AUDIO_H

#include "utils.h"
#include "mixer.h"

/// Loads all audio
/// @param Count    where to store numnber of samples
/// @return all samples
Mix_Chunk * InitializeAudio(int * Count);

/// Unloads all audio
/// @param Chuncks  all audio
/// @param Count    number of samples
void DestroyAudio(Mix_Chunk * Chunks, int Count);

#endif
