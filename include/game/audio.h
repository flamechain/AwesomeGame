#ifndef AUDIO_H
#define AUDIO_H

#include "utils.h"
#include "mixer.h"

/// Loads all audio
/// @param count    where to store numnber of samples
/// @param data     where to store the samples
void InitializeAudio(long long unsigned int& count, vector<Mix_Chunk>& data);

/// Unloads all audio
/// @param data     all audio chunks
/// @param count    number of samples
void DestroyAudio(vector<Mix_Chunk>& data, long long unsigned int count);

#endif
