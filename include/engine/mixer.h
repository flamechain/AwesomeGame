#ifndef MIXER_H
#define MIXER_H

#include "utils.h"

#define FREQUENCY 44100
#define CHANNELS 2
#define CHUNKSIZE 512

/// Load audio chunk from file
/// @param filename file to open
/// @return new chunk of audio
Mix_Chunk *LoadWAV(string filename);


#endif
