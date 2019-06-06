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
	//std::string imagesPath[FRAME][STREAM];
	std::vector<std::vector<std::string>> imagePaths;
	SDL_Texture* currentTexture;
	Vec2 position;

	int imageIndex;
	Vec2 angle;
	int frame, stream;

public:

	ScannedObject(SDL_Renderer* canvas);
	void init();
	void update(float secs);
	void draw();
	void deinit();
	SDL_Texture* getImageFromAngle();
	void incrementAngle(const Vec2& increment);
	SDL_Texture* getCurrentTexture();
	ScannedObject* getActualObject();
	void setupImages(std::string path);
};