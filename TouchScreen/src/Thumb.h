#pragma once
#include <SDL.h>
#include <string>
#include "EventListener.h"
#include "MathVectors.h"

class Thumb : public EventListener {

private:
	SDL_Texture* circle;
	SDL_Renderer* canvas;
	SDL_Rect* backgroundRect;
	SDL_Rect* joystickRect;
	Vec2 inputVector;
	
	float radius;
	float joystickRadius;
public:
	Thumb(float radius);
	void init(SDL_Renderer* canvas);
	void update();
	void draw();
	void deinit();
	SDL_Texture* loadTexture(std::string path);
	bool loadMedia();
	Vec2 getInputVector() const;

	void onMouseButtonHold();
	void onMouseButtonUp();
};