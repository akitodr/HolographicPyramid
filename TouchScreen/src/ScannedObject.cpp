#include "ScannedObject.h"
#include "ImageLoader.h"
#include <filesystem>
#include <iostream>
#include "Reader.h"

ScannedObject::ScannedObject(SDL_Renderer* canvas)
	: canvas(canvas) {}

void ScannedObject::init()
{
}

void ScannedObject::update(float secs)
{

}

void ScannedObject::draw()
{
	int imageW, imageH, w, h;
	SDL_QueryTexture(currentTexture, NULL, NULL, &imageW, &imageH);
	SDL_GetRendererOutputSize(canvas, &w, &h);

	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = h * (imageH / imageW);
	rect.h = h;

	SDL_RenderCopy(canvas, currentTexture, NULL, &rect);
}

void ScannedObject::deinit()
{
	SDL_DestroyTexture(currentTexture);
}

SDL_Texture * ScannedObject::getImageFromAngle()
{
	int imgX = (frame - 1) * (angle.y / 360);
	int imgY = (stream - 1) * (angle.x / 90);

	return loadTexture(canvas, imagePaths[imgX][imgY]);
}

void ScannedObject::incrementAngle(const Vec2& increment)
{
	int oldImgX = (frame - 1) * (angle.y / 360);
	int oldImgY = (stream - 1) * (angle.x / 90);

	angle.x += increment.y;
	angle.y += increment.x;

	if (angle.x < 0) angle.x = 0;
	if (angle.x > 90) angle.x = 90;

	if (angle.y >= 360) angle.y = angle.y - 360;
	if (angle.y < 0) angle.y = angle.y + 360;

	int newImgX = (frame - 1) * (angle.y / 360);
	int newImgY = (stream - 1) * (angle.x / 90);

	if (oldImgX != newImgX || oldImgY != newImgY)
	{
		SDL_DestroyTexture(currentTexture);
		currentTexture = getImageFromAngle();
	}
}

SDL_Texture* ScannedObject::getCurrentTexture()
{
	return currentTexture;
}

ScannedObject* ScannedObject::getActualObject()
{
	return this;
}

void ScannedObject::setupImages(std::string path)
{
	this->path = path;
	frame = readFile(path + "configf2s2.cfg", "Frames:");
	stream = readFile(path + "configf2s2.cfg", "Streams:");

	imagePaths.clear();

	for (int i = 0; i < frame; i++)
	{
		std::vector<std::string> column(stream, " ");
		imagePaths.push_back(column);
	}

	int index = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string path = entry.path().string();
		std::string extension = path.substr(path.length() - 4);
		if (extension != ".png")
			continue;

		int x = index % frame;
		int y = index / frame;

		imagePaths.at(x).at(y) = (path);
		index++;
	}

	imageIndex = 0;
	angle.x = 45;
	angle.y = 45;

	currentTexture = getImageFromAngle();
}
