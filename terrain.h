#include<math.h>

float generateNoise(float x, float y, int width, int height, int salt);

float smoothstep(float x);

float biLerp(float x, float y, int x1, int x2, int y1, int y2, float v1, float v2, float v3, float v4);

int hash (int a1, int a2, int a3);