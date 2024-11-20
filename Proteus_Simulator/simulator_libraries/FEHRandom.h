#ifndef FEHRANDOM_H
#define FEHRANDOM_H

#include <stdlib.h>

class FEHRandom
{
public:
	/// @brief Seed the random number generator
	void Seed();

	/// @brief Get a random integer between 0 and 32767
	int RandInt();
};

extern FEHRandom Random;

#endif // FEHRANDOM_H
