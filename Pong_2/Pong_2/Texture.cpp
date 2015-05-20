#include "Texture.h"
#include <SDL_image.h>

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}
bool Texture::loadFromFile(string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
	}
	SDL_FreeSurface(loadedSurface);
	texture = newTexture;
	return texture != NULL;
}
void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}