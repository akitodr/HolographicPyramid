#include "ScannedObject.h"
#include "ImageLoader.h"
#include <filesystem>
#include <iostream>

ScannedObject::ScannedObject(SDL_Renderer* canvas, std::string path) 
							: canvas(canvas), path(path) {}

void ScannedObject::init()
{
	int index = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string path = entry.path().string();
		std::string extension = path.substr(path.length() - 4);
		if (extension != ".png")
			continue;

		int x = index % FRAME;
		int y = index / FRAME;

		std::cout << "(" << x << ", " << y << ") = " << entry.path().string() << std::endl;
		images[x][y] = loadTexture(canvas, entry.path().string());

		index++;
	}

	imageIndex = 0;
}

void ScannedObject::update(float secs)
{

}

void ScannedObject::draw()
{
	if (imageIndex >= FRAME * STREAM)
		imageIndex = 0;

	SDL_Texture* currentTexture = images[imageIndex % FRAME][imageIndex / FRAME];
	
	SDL_RenderCopy(canvas, currentTexture, NULL, NULL);

	imageIndex++;

	currentTexture = NULL;
}

void ScannedObject::deinit()
{
	for (int y = 0; y < STREAM; y++)
	{
		for (int x = 0; x < FRAME; x++)
		{
			SDL_DestroyTexture(images[x][y]);
		}
	}
}
