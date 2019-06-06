#include "Button.h"
#include <stdio.h>
#include "ImageLoader.h"
#include "InputHandler.h"

Button::Button(SDL_Renderer* canvas, int posX, int posY, int w, int h, bool right = true)
{
	this->canvas = canvas;
	rect.x = posX;
	rect.y = posY;
	rect.w = w;
	rect.h = h;
	this->right = right;
}

void Button::init()
{
	texture = loadTexture(canvas, "arrow.png");
	InputHandler::instance().addListener(this);
}

void Button::update()
{
	clicked = false;
}

void Button::draw()
{
	if(right)
		SDL_RenderCopy(canvas, texture, NULL, &rect);
	else
		SDL_RenderCopyEx(canvas, texture, NULL, &rect, 0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
}

void Button::deinit()
{
}

void Button::onMouseButtonDown()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Point mousePoint;
	mousePoint.x = x;
	mousePoint.y = y;
	if (SDL_PointInRect(&mousePoint, &rect))
	{
		clicked = true;
	}
}

bool Button::isClicked()
{
	return clicked;
}
