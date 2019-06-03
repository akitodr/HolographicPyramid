#pragma once
#include <SDL.h>

class Button {
private:
	int pos_x, pos_y, width, height;
	bool isDown;
	SDL_Surface circle;

public:
	Button(int posX, int posY, int w, int h);
	void init();
	void update();
	void draw(SDL_Renderer* canvas);
	void deinit();
};