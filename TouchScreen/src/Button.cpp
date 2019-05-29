#include "Button.h"
#include <stdio.h>

Button::Button(int posX, int posY, int w, int h)
		: pos_x(posX), pos_y(posY), width(w), height(h) {}

void Button::init()
{
	isDown = false;
}

void Button::update()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit (inputs)
		if (isDown && !(e.type == SDL_MOUSEBUTTONDOWN))
		{
			printf("mouse down");
			isDown = false;
			return;
		}
		
		if (!isDown && isHovered(&e) && (e.type == SDL_MOUSEBUTTONDOWN))
		{
			printf("mouse down");
			isDown = false;
			return;
		}
	}
}

void Button::draw(SDL_Renderer* canvas)
{

	SDL_Rect fillRect = { 1366 / 4, 768 / 4, 1366 / 2, 768 / 2 };

	if(isDown) SDL_SetRenderDrawColor(canvas, 0x74, 0x2A, 0x7F, 0xFF);
	else SDL_SetRenderDrawColor(canvas, 0xFF, 0x00, 0x00, 0xFF);

	SDL_RenderFillRect(canvas, &fillRect);

}

void Button::deinit()
{
}

bool Button::isHovered(SDL_Event* e)
{
	int x, y;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
	}

	return (x >= pos_x && x <= pos_x + width &&
			y >= pos_y && y <= pos_y + height);
}
