#pragma once
#include <SDL.h>
#include "EventListener.h"

class Button : public EventListener {
private:
	SDL_Rect rect;
	SDL_Renderer* canvas;
	SDL_Texture* texture;
	bool clicked;
	bool right;

public:
	Button(SDL_Renderer* canvas, int posX, int posY, int w, int h, bool right);
	void init();
	void update();
	void draw();
	void deinit();
	Vec2 getTextureSize();
	void setPosition(const Vec2& pos);

	void onMouseButtonDown();

	bool isClicked();
};