#include "terrain.h"

float generateNoise(float x, float y, int width, int height, int salt) {
	//divide the coordinates by the size to normalize the coordinates to a decimal.
	//so if x=18 and width=16, this will turn x into 1.125, which is how coordinates will be used
	
	x = fabs(x/width);//this function cannot handle negative coordinates, so fabs (floating abs) is required.
	y = fabs(y/height);//The side effect is that everything is mirrored on the x/y axis :(


	//generate normalized x/y coords for each anchor point around the real point
	int x1 = (int) floor(x);
	int x2 = (int) floor(x) + 1;
	int y1 = (int) floor(y);
	int y2 = (int) floor(y) + 1;
	
	//get a noise value for each anchor between 0 and 1
	//1024 chosen arbitrarily for normalization
	//we divide by 1023, because because <any number> % 1024 can at most only be 1023.
	float a1 = smoothstep( (float) (hash(x1, y1, salt) % 1024) / 1023);
	float a2 = smoothstep( (float) (hash(x2, y1, salt) % 1024) / 1023);
	float a3 = smoothstep( (float) (hash(x1, y2, salt) % 1024) / 1023);
	float a4 = smoothstep( (float) (hash(x2, y2, salt) % 1024) / 1023);
	
	return biLerp(x, y, x1, x2, y1, y2, a1, a2, a3, a4);
}

float smoothstep(float x) {
	//smooth out the curve, so there are no harsh edges on the perimiter of anchor squares.
	//return x; //no smoothing
	return x*x*x*(x*(x*6 - 15) + 10); //smoothstep
	//return -20*pow(x,7) + 70*pow(x,6) - 84*pow(x, 5) + 35*pow(x,4); //Smootherstep
}

float biLerp(float x, float y, int x1, int x2, int y1, int y2, float v1, float v2, float v3, float v4) {
	/*	v1---v2
		|     |
		|     |
		v3---v4*/
    return 1.f / ((x2 - x1) * (y2 - y1)) * (v1 * (x2 - x) * (y2 - y) + v2 * (x - x1) * (y2 - y) + v3 * (x2 - x) * (y - y1) + v4 * (x - x1) * (y - y1));
}

int hash (int a1, int a2, int a3) {
	int seed = (( a1 + a2) * (a1 + a2 + 1)) / 2 + a2;
	seed = (( seed + a3) * (seed + a3 + 1)) / 2 + a3;
	
    seed = ((seed >> 16) ^ seed) * 0x45d9f3b;
    seed = ((seed >> 16) ^ seed) * 0x45d9f3b;
    seed = (seed >> 16) ^ seed;
    return seed;	
}