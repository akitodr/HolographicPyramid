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
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
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

	thumb = new Thumb(300);
	thumb->init(canvas);
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

		//SDL_SetRenderDrawColor(canvas, 0xFF, 0xFF, 0xFF, 0xFF);
		//SDL_Rect fillRect = { 1366 / 4, 768 / 4, 1366 / 2, 768 / 2 };
		thumb->update();
		thumb->draw();
		std::cout << thumb->getInputVector().x << ", " << thumb->getInputVector().y << std::endl;

		//[Render red filled quad
		/*SDL_SetRenderDrawColor(canvas, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(canvas, &fillRect);*/

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
	thumb->deinit();
	close();
}

void Window::close() {

	//Destroy window
	SDL_DestroyRenderer(canvas);
	SDL_DestroyWindow(window);
	canvas = NULL;
	window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Window::getCanvas() const
{
	return canvas;
}


