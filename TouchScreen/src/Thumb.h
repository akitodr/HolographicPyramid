#pragma once
#include <SDL.h>
#include <string>
#include "EventListener.h"
#include "MathVectors.h"

class Thumb : public EventListener {

private:
	SDL_Texture* circle;
	SDL_Texture* circle1;
	SDL_Renderer* canvas;
	SDL_Rect* backgroundRect;
	SDL_Rect* joystickRect;
	Vec2 inputVector;
	Vec2 position;

	float radius;
	float joystickRadius;

	bool isHolding;
public:
	Thumb(float radius, const Vec2& pos);
	void init(SDL_Renderer* canvas);
	void update();
	void draw();
	void deinit();
	bool loadMedia();
	Vec2 getInputVector() const;

	void onMouseButtonHold();
	void onMouseButtonUp();
	void onMouseButtonDown();
	

	void onTouchHold(const Vec2& fingerPos);
	void onTouchUp(const Vec2& fingerPos);
	void onTouchDown(const Vec2& fingerPos);

};