#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
using namespace std;
#ifndef TEXTURE_H_
#define TEXTURE_H_
class Texture
{
public:
	Texture();
	bool loadFromFile(string path, SDL_Renderer* renderer);
	bool loadFromRenderedText(string path, SDL_Color color, SDL_Renderer* renderer);
	void free();
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture* texture;
	int width;
	int height;
	TTF_Font *gFont;
};
#endif