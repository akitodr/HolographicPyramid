#include "TouchWindow.h"
#include <stdio.h>
#include <SDL_image.h>
#include "InputHandler.h"


TouchWindow::TouchWindow(const char* title) : title(title) {}

TouchWindow::TouchWindow() : TouchWindow("TouchPad") {}

void TouchWindow::init()
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
		window = SDL_CreateWindow(title, -1920, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);
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

	thumb = new Thumb(200, Vec2(1920 - 300, 1080 - 300));
	thumb->init(canvas);
	object = new ScannedObject(canvas, "vader\\");
	object->init();
}

void TouchWindow::loop() {
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


		thumb->update();

		object->incrementAngle(Vec2(thumb->getInputVector().x, -thumb->getInputVector().y) * 10);
		object->update(secs);
		object->draw();

		thumb->draw();

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
	object->deinit();
	close();
}

void TouchWindow::close() {

	//Destroy window
	SDL_DestroyRenderer(canvas);
	SDL_DestroyWindow(window);
	delete thumb;
	delete object;
	canvas = NULL;
	window = NULL;
	thumb = NULL;
	object = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* TouchWindow::getCanvas() const
{
	return canvas;
}
