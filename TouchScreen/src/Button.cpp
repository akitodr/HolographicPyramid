#include "Button.h"
#include <stdio.h>

Button::Button(int posX, int posY, int w, int h)
		: pos_x(posX), pos_y(posY), width(w), height(h) {}

void Button::init()
{
	
}

void Button::update()
{
	
}

void Button::draw(SDL_Renderer* canvas)
{

	/*SDL_Rect fillRect = { 1366 / 4, 768 / 4, 1366 / 2, 768 / 2 };

	if(isDown) SDL_SetRenderDrawColor(canvas, 0x74, 0x2A, 0x7F, 0xFF);
	else SDL_SetRenderDrawColor(canvas, 0xFF, 0x00, 0x00, 0xFF);

	SDL_RenderFillRect(canvas, &fillRect);*/



}

void Button::deinit()
{
}
