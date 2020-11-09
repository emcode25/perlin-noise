#ifndef PERLIN_H
#define PERLIN_H

#define PERMUTATION_SIZE 256
#define genericNoise2D(x, y, p) noise2D_FBM(x, y, p, 200, 8, 2.0f, 0.5f)

/**
* \brief Initializes and shuffles the hash array.
* \param p: Pointer to a hash array of size PERMUTATION_SIZE (256).
*/
void shuffleHash(int* p);

/**
* \brief Restricts a value to a min/max value (float).
* \param value: The value to be restricted.
* \param min: The minimum the value can be restricted to.
* \param max: The maximum the value can be restricted to.
* \return The clamped value.
*/
float clampf(float value, float min, float max);

/**
* \brief Linearly interpolates a value to a range.
* \param value: The value to be interpolated.
* \param min: The minimum the value can be interpolated to.
* \param max: The maximum the value can be interpolated to.
* \return The interpolated value.
*/
float lerpf(float value, float min, float max);

/**
* \brief Outputs a value based on a hash table using 2D Perlin Noise.
* \param x: The x value on the grid.
* \param y: The y value on the grid.
* \param p: Pointer to the hash table to calculate noise from.
* \return The intensity of the point.
*/
float noise2D(float x, float y, int* p);

/**
* \brief Outputs a value based on a hash table using 2D Perlin Noise and Fractal Brownian Motion (FBM) to give a more natural feel.
* \param x: The x value on the grid.
* \param y: The y value on the grid.
* \param p: Pointer to the hash table to calculate noise from.
* \param scale: How close the view of the grid should be.
* \param octaves: The number of waves combined.
* \param lacunarity: The frequency factor each subsequent wave will be.
* \param persistence: The amplitude factor of each subsequent wave.
* \return The intensity of the point.
*/
float noise2D_FBM(float x, float y, int* p, float scale, int octaves, float lacunarity, float persistence);

#endif