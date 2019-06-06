#include "Window.h"
#include <stdio.h>
#include <SDL_image.h>
#include "InputHandler.h"


Window::Window(const char* title) : title(title) {}

Window::Window() : Window("TouchPad") {}

void Window::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow(title, 1920, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			canvas = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (canvas == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else {


				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}
			}
		}
	}



	object = new ScannedObject(canvas);
	object->init();
	setupRect();
	time = SDL_GetTicks();
}

void Window::loop() {
	
}

void Window::update()
{
	float secs = (SDL_GetTicks() - time) / 1000;
	time = SDL_GetTicks();

	//F64740
	SDL_SetRenderDrawColor(canvas, 0x00, 0x00, 0x00, 0xFF);
	//Clear screen
	SDL_RenderClear(canvas);

	Vec2 inputVector = Vec2(thumb->getInputVector().x, -thumb->getInputVector().y);
	if (inputVector.x == 0 && inputVector.y == 0) {
		delayCounter += secs;
	}
	else {
		object->incrementAngle(Vec2(thumb->getInputVector().x, -thumb->getInputVector().y) * 100 * secs);
		delayCounter = 0;
	}

	if (delayCounter >= animationDelay) {
		object->incrementAngle(Vec2(0.5, 0) * 100 * secs);
	}


	//object->incrementAngle(Vec2(thumb->getInputVector().x, -thumb->getInputVector().y) * 100 * secs);
	object->update(secs);

	SDL_Texture * texture = object->getCurrentTexture();
	SDL_RenderCopyEx(canvas, texture, NULL, &rect, 0, &pivot, SDL_RendererFlip::SDL_FLIP_VERTICAL);
	SDL_RenderCopyEx(canvas, texture, NULL, &rect, -90, &pivot, SDL_RendererFlip::SDL_FLIP_VERTICAL);
	SDL_RenderCopyEx(canvas, texture, NULL, &rect, 90, &pivot, SDL_RendererFlip::SDL_FLIP_VERTICAL);

	/*SDL_SetRenderDrawColor(canvas, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderSetScale(canvas, 10,10);
	SDL_RenderDrawPoint(canvas, pivot.x, pivot.y);*/

	//thumb->draw();
	SDL_RenderPresent(canvas);
}

void Window::close() {
	object->deinit();

	//Destroy window
	SDL_DestroyRenderer(canvas);
	SDL_DestroyWindow(window);
	delete object;
	canvas = NULL;
	window = NULL;
	object = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Window::getCanvas() const
{
	return canvas;
}

void Window::setupRect()
{
	int w, h;
	SDL_GetRendererOutputSize(canvas, &w, &h);

	int imgW, imgH;
	SDL_QueryTexture(object->getCurrentTexture(), NULL, NULL, &imgW, &imgH);

	float proportion = (float)imgW / imgH;

	float blankSpot = h * 0.50;

	float yOffset = -h * 0.02f;

	rect.h = h - blankSpot;
	rect.w = rect.h * proportion;
	rect.x = (w * 0.5) - rect.w / 2;
	rect.y = yOffset;

	pivot.x = rect.w / 2;
	pivot.y = h - yOffset - blankSpot / 2;
}

void Window::setThumb(Thumb* thumb)
{
	this->thumb = thumb;
}

void Window::setObjectPath(std::string path)
{
	object->setupImages(path);
}

