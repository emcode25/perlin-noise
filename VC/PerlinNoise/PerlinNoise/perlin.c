#include "perlin.h"

#include <stdlib.h>
#include <time.h>

void shuffleHash(int* p)
{
	srand(time(NULL)); //Ensure that the randomness is truly random

	for(int i = 0; i < PERMUTATION_SIZE; ++i) //Reset array
	{
		p[i] = i;
	}

	for (int i = PERMUTATION_SIZE - 1; i > 0; --i) //Randomly shuffle using Fisher-Yates alogrithm
	{
		int j = rand() % (i + 1);
		int hold = p[i];
		p[i] = p[j];
		p[j] = hold;
	}
}

int* allocHash(void)
{
	int* array = malloc(PERMUTATION_SIZE * sizeof(int));
	
	shuffleHash(array);

	return array;
}

int* freeHash(int* p)
{
	free(p);

	return NULL;
}

float clampf(float value, float min, float max)
{
	return (value < min) ? min : ((value > max) ? max : value);
}

float lerpf(float value, float min, float max)
{
	return (max - min) * value + min;
}

//Calculates a gradient and dot product based on a hash (subject to change?)
float grad(int hash, float x, float y)
{
	return ((hash & 1) ? x : -x) + ((hash & 2) ? y : -y);
}

//Smoothens a value for interpolation
float fade(float v)
{
	return ((6 * v - 15) * v + 10) * v * v * v;
}

float noise2D(float x, float y, int* p)
{
	int X0, X1, Y0, Y1; //Holds the hash indices
	float u, v; //Faded values of x and y respectively

	//Calculate indices
	X0 = (int)x & 255;
	Y0 = (int)y & 255;
	X1 = (X0 + 1) & 255;
	Y1 = (Y0 + 1) & 255;

	//Find the lengths of the offset vector's components
	x -= (int)x;
	y -= (int)y;

	//Calculate faded values for interpolation
	u = fade(x);
	v = fade(y);

	//Find hashes for gradient vectors
	int bottomLeft = p[(p[X0] + Y0) & 255];
	int bottomRight = p[(p[X1] + Y0) & 255];
	int topLeft = p[(p[X0] + Y1) & 255];
	int topRight = p[(p[X1] + Y1) & 255];

	//Calculate dot products of vectors based on hashes
	float BLdot = grad(bottomLeft, x, y);
	float BRdot = grad(bottomRight, x - 1, y);
	float TLdot = grad(topLeft, x, y - 1);
	float TRdot = grad(topRight, x - 1, y - 1);

	//Calculate final intensity
	return lerpf(v, lerpf(u, BLdot, BRdot),
					lerpf(u, TLdot, TRdot));
}

float noise2D_FBM(float x, float y, int* p, float scale, int octaves, float lacunarity, float persistence)
{
	float noise = 0.0f; //Sum of all waves
	float a = 1.0f; //Initial amplitude
	float f = 1 / scale; //Frequency

	for (int i = 0; i < octaves; ++i)
	{
		noise += a * noise2D(x * f, y * f, p);

		f *= lacunarity; //Modify frequency
		a *= persistence; //Modify amplitude
	}

	return noise;
}
