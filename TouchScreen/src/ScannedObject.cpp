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
		imagesPath[x][y] = (path);
		//images[x][y] = loadTexture(canvas, entry.path().string());

		index++;
	}

	imageIndex = 0;
	angle.x = 45;
	angle.y = 45;
}

void ScannedObject::update(float secs)
{

}

void ScannedObject::draw()
{
	SDL_Texture* currentTexture = getImageFromAngle();

	int imageW, imageH, w, h;
	SDL_QueryTexture(currentTexture, NULL, NULL, &imageW, &imageH);
	SDL_GetRendererOutputSize(canvas, &w, &h);

	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = h * (imageH / imageW);
	rect.h = h;

	SDL_RenderCopy(canvas, currentTexture, NULL, &rect);

	SDL_DestroyTexture(currentTexture);
	currentTexture = NULL;
}

void ScannedObject::deinit()
{
	
}

SDL_Texture * ScannedObject::getImageFromAngle()
{
	int imgX = (FRAME - 1) * (angle.y / 360);
	int imgY = (STREAM - 1) * (angle.x / 90);

	return loadTexture(canvas, imagesPath[imgX][imgY]);
}

void ScannedObject::incrementAngle(const Vec2& increment)
{
	angle.x += increment.y;
	angle.y += increment.x;

	if (angle.x < 0) angle.x = 0;
	if (angle.x > 90) angle.x = 90;

	if (angle.y >= 360) angle.y = angle.y - 360;
	if (angle.y < 0) angle.y = angle.y + 360;
}
