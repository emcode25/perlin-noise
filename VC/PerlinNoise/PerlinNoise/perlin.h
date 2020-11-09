#ifndef PERLIN_H
#define PERLIN_H

#define PERMUTATION_SIZE 256

/**
* \brief Initializes and shuffles the hash array.
* \param p: Pointer to a hash array of size PERMUTATION_SIZE (256).
*/
void shuffleHash(int* p);

/**
* \brief Dynamically allocates and shuffles a hash array.
* \return A dynamically allocated filled hash array.
*/
int* allocHash(void);

/**
* \brief Frees a dynamically allocated hash array.
* \param p: Pointer to a dynamically allocated hash array.
* \returns A null pointer.
*/
int* freeHash(int* p);

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
* \brief Outputs a value based on a hash array using 2D Perlin Noise.
* \param x: The x value on the grid.
* \param y: The y value on the grid.
* \param p: Pointer to the hash array to calculate noise from (the table must be pre-initialized by shuffleHash or allocHash).
* \return The intensity of the point (from 0 to 1, inclusive).
*/
float noise2D(float x, float y, int* p);

/**
* \brief Outputs a value based on a hash array using 2D Perlin Noise and Fractal Brownian Motion (FBM) to give a more natural feel.
* \param x: The x value on the grid.
* \param y: The y value on the grid.
* \param p: Pointer to the hash array to calculate noise from (the table must be pre-initialized by shuffleHash or allocHash).
* \param scale: How close the view of the grid should be.
* \param octaves: The number of waves combined.
* \param lacunarity: The frequency factor each subsequent wave will be.
* \param persistence: The amplitude factor of each subsequent wave.
* \return The intensity of the point (can be below 0 or above 1).
*/
float noise2D_FBM(float x, float y, int* p, float scale, int octaves, float lacunarity, float persistence);

/**
* \brief Outputs a value based on a hash table using 2D Perlin Noise and generic Fractal Brownian Motion settings (FBM).
* \param x: The x value on the grid.
* \param y: The y value on the grid.
* \param p: Pointer to the hash array to calculate noise from (the table must be pre-initialized by shuffleHash or allocHash).
* \param scale: 200
* \param octaves: 8
* \param lacunarity: 2.0
* \param persistence: 0.5
* \return The intensity of the point (can be below 0 or above 1).
*/
#define genericNoise2D(x, y, p) noise2D_FBM(x, y, p, 200, 8, 2.0f, 0.5f)

#endif