#pragma once
#include <string>
#include <SDL.h>
#include <vector>
#include "MathVectors.h"

#define STREAM 15
#define FRAME 60

class ScannedObject {
private:
	std::string path;
	SDL_Renderer* canvas;
	std::string imagesPath[FRAME][STREAM];
	Vec2 position;

	int imageIndex;
	Vec2 angle;

public:

	ScannedObject(SDL_Renderer* canvas, std::string path);
	void init();
	void update(float secs);
	void draw();
	void deinit();
	SDL_Texture* getImageFromAngle();
	void incrementAngle(const Vec2& increment);
	ScannedObject* getActualObject();
};