#pragma once
#include <string>
#include <SDL.h>
#include <vector>

#define STREAM 16
#define FRAME 60

class ScannedObject {
private:
	std::string path;
	SDL_Renderer* canvas;
	SDL_Texture* images[FRAME][STREAM];

	int imageIndex;

public:

	ScannedObject(SDL_Renderer* canvas, std::string path);
	void init();
	void update(float secs);
	void draw();
	void deinit();
};