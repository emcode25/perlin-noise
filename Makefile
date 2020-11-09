#This may work? Not tested.
all:
	gcc -c ./src/perlin.c
	ar -crs libPerlinNoise.a perlin.o
	rm perlin.o