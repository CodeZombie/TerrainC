#include "SDL/SDL.h" 
#include <stdio.h>
#include "terrain.h"

int drawPixel(SDL_Renderer *renderer_, int x_, int y_, int red_, int green_, int blue_) {
	SDL_SetRenderDrawColor(renderer_, red_, green_, blue_, 255);
	SDL_RenderDrawPoint(renderer_, x_, y_);
	return 1;
}

int drawRect(SDL_Renderer *renderer_, int x_, int y_, int w_, int h_, int red_, int green_, int blue_) {
	SDL_SetRenderDrawColor(renderer_, red_, green_, blue_, 255);
	SDL_Rect r;
	r.x = x_;
	r.y = y_;
	r.w = w_;
	r.h = h_;
	SDL_RenderFillRect(renderer_, &r);
	return 1;
}

int isKeyDown(SDL_Keycode k_) {
	SDL_PumpEvents();
	const Uint8 * keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_GetScancodeFromKey(k_)]) {
		return 1;
	}
	return 0;
}

int main( int argc, char* args[] ) {

	
	printf("Initializing game...\n");
	
	int gameRunning = 1;
	int tileSize = 4;
	float cameraOffsetX = 0;
	float cameraOffsetY = 0;
	int windowWidth = 800;
	int windowHeight = 800;

	//temp vars
	int r, g, b;
	float value = 0;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;
	SDL_Window *gameWindow = SDL_CreateWindow("Terrain Generator!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	SDL_Renderer *gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

	printf("Starting game loop...\n");
	
	while(gameRunning) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			break;
		}
		while(SDL_PollEvent( &event )) {
			switch(event.type) {
				case SDL_QUIT:
					gameRunning = 0;
					break;
					
			}
		}
		
		if(isKeyDown(SDLK_a)) {
			cameraOffsetX-=2;
		}
		if(isKeyDown(SDLK_d)) {
			cameraOffsetX+=2;	
		}
		if(isKeyDown(SDLK_w)) {
			cameraOffsetY-=2;		
		}
		if(isKeyDown(SDLK_s)) {
			cameraOffsetY+=2;	
		}
		
		for(int y = 0; y < windowHeight/tileSize; y++) {
			for(int x = 0; x < windowWidth/tileSize; x++) {
				
				r = generateNoise((float)x + cameraOffsetX, (float)y + cameraOffsetY, 4, 4, 256)*255;
				//g = generateNoise((float)x + cameraOffsetX, (float)y + cameraOffsetY, 50/tileSize, 50/tileSize, 1332)*255;
				//b = generateNoise((float)x + cameraOffsetX, (float)y + cameraOffsetY, 50/tileSize, 50/tileSize, 552)*255;
				/*
					if (value > 0 && value < 0.1) {
						//dark blue
						r = 11;
						g = 73;
						b = 113;	
					}else if(value > 0.1 && value < 0.15) {
						//light blue
						r = 155;
						g = 218;
						b = 243;	
					}else if(value > 0.15 && value < 0.25) {
						//light sand
						r = 240;
						g = 194;
						b = 59;						
					}else if(value > 0.25 && value < 0.4) {
						//light grass
						r = 146;
						g = 199;
						b = 73;						
					}else if(value > 0.4 && value < 0.8) {
						//dark grass
						r = 63;
						g = 101;
						b = 45;						
					}else if(value > 0.8 && value < 0.9) {
						//light rock
						r = 60;
						g = 60;
						b = 60;						
					}else if(value > 0.9 && value < 1) {
						//dark rock
						r = 13;
						g = 13;
						b = 13;						
					}
					*/
					r = (int)(r/32) * 32;
				drawRect(gameRenderer, x*tileSize, y*tileSize, tileSize, tileSize, r, r, r);
			}
		}
		SDL_RenderPresent(gameRenderer);
	}
	printf("Ending game...\n");
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	return 0; 
}