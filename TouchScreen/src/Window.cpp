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
		window = SDL_CreateWindow(title, 0, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);
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

	setupRect();

	//object = new ScannedObject(canvas, "vader\\");
	object->init();
}

void Window::loop() {
	//Main loop flag
	bool quit = false;

	SDL_Event e;

	init();

	//While application is running
	while (!quit)
	{
		float secs = SDL_GetTicks() / 1000.f;

		InputHandler::instance().update();

		//F64740
		SDL_SetRenderDrawColor(canvas, 0x00, 0x00, 0x00, 0xFF);
		//Clear screen
		SDL_RenderClear(canvas);


		//object->incrementAngle(Vec2(thumb->getInputVector().x, -thumb->getInputVector().y) * 10);
		object->update(secs);


		SDL_Texture* texture = object->getImageFromAngle();
		SDL_RenderCopyEx(canvas, texture, NULL, &rect, 0, &pivot, SDL_RendererFlip::SDL_FLIP_VERTICAL);
		SDL_RenderCopyEx(canvas, texture, NULL, &rect, -90, &pivot, SDL_RendererFlip::SDL_FLIP_VERTICAL);
		SDL_RenderCopyEx(canvas, texture, NULL, &rect, 90, &pivot, SDL_RendererFlip::SDL_FLIP_VERTICAL);
		

		//thumb->draw();
		SDL_RenderPresent(canvas);

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit (inputs)
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			InputHandler::instance().handleInput(e);
		}
	}
	object->deinit();
	close();
}

void Window::close() {

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

	float blankSpot = h * 0.34;
	
	rect.x = (w * 0.5) - blankSpot/2;
	rect.y = 0;
	rect.w = blankSpot;
	rect.h = h - blankSpot;

	pivot.x = rect.w / 2;
	pivot.y = h - blankSpot /2;
}

void Window::setObject(ScannedObject * object)
{
	this->object = object;
}
