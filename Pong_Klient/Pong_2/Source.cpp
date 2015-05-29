#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int Paddle_VEL = 5;
const int BALL_SPEED = -6;
const float MAX_BOUND_ANGLE = 5 * M_PI / 12;
float relativeIntersectY;
float normalizedRelativeIntersectionY;
float bounceAngle;
class Texture
{
public:
	Texture();
	bool loadFromFile(string path);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture* texture;
	int width;
	int height;
};
class Paddle
{
public:
	Paddle();
	void setPosition(float posX, float posY, int width, int height);
	void moveHorizontal();
	void moveVertical();
	void render(int type);
	float posX, posY;
	int paddleWidth, paddleHeight;
	int velX, velY;
	int index;
};
class Ball
{
public:
	Ball();
	void setPosition(float posX, float posY, int width, int height);
	void render();
	void move();
	float posX, posY;
	int ballWidth, ballHeight;
	float velX, velY;
};
class Event
{
public:
	Event();
	void setPosition(float posX, float posY, int width, int height);
	void render();
	float posX, posY;
	bool inactive;
	int eventWidth, eventHeight;
};
bool init();
bool loadSprite();
void close();
int reflection(int index, int type);
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Paddle paddles[4];
Ball ball;
Event speed;
Texture horizontalPaddle, verticalPaddle, balTexture, speedTexture;
Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}
bool Texture::loadFromFile(string path)
{
	free();
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
void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}
Paddle::Paddle()
{
}
void Paddle::setPosition(float x, float y, int width, int height)
{
	posX = x;
	posY = y;
	paddleWidth = width;
	paddleHeight = height;
	velX = 0;
	velY = 0;
}
void handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
				case SDLK_LEFT: paddles[0].velX -= Paddle_VEL; break;
				case SDLK_RIGHT: paddles[0].velX += Paddle_VEL; break;
				case SDLK_a: paddles[1].velX -= Paddle_VEL; break;
				case SDLK_d: paddles[1].velX += Paddle_VEL; break;
				case SDLK_i: paddles[2].velY -= Paddle_VEL; break;
				case SDLK_k: paddles[2].velY += Paddle_VEL; break;
				case SDLK_y: paddles[3].velY -= Paddle_VEL; break;
				case SDLK_h: paddles[3].velY += Paddle_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: paddles[0].velX += Paddle_VEL; break;
		case SDLK_RIGHT: paddles[0].velX -= Paddle_VEL; break;
		case SDLK_a: paddles[1].velX += Paddle_VEL; break;
		case SDLK_d: paddles[1].velX -= Paddle_VEL; break;
		case SDLK_i: paddles[2].velY += Paddle_VEL; break;
		case SDLK_k: paddles[2].velY -= Paddle_VEL; break;
		case SDLK_y: paddles[3].velY += Paddle_VEL; break;
		case SDLK_h: paddles[3].velY -= Paddle_VEL; break;
		}
	}
}
void Paddle::moveHorizontal()
{
	posX += velX;
	if ((posX < 0) || (posX + paddleWidth > SCREEN_WIDTH))
	{
		posX -= velX;
	}
}
void Paddle::moveVertical()
{
	posY += velY;
	if ((posY < 0) || (posY + paddleHeight > SCREEN_HEIGHT))
	{
		posY -= velY;
	}
}
void Paddle::render(int type)
{
	if (type == 1)
	{
		horizontalPaddle.render(posX, posY);
	}
	else
	{
		verticalPaddle.render(posX, posY);
	}
}
Ball::Ball()
{
}
void Ball::setPosition(float x, float y, int width, int height)
{
	posX = x;
	posY = y;
	ballWidth = width;
	ballHeight = height;
	velX = -BALL_SPEED;
	velY = 0;
}
void Ball::render()
{
	balTexture.render(posX, posY);
}
void Ball::move()
{
	posX += velX;
	posY += velY;
	if (posY < speed.posY + speed.eventHeight && posY + ballHeight > speed.posY
		&& posX < speed.posX + speed.eventWidth && posX + ballWidth > speed.posX && speed.inactive == false)
	{
		velX *= 2;
		velY *= 2;	
		speed.inactive = true;
	}
	if (posY + ballHeight > paddles[0].posY && posX > paddles[0].posX && posX < paddles[0].posX + paddles[0].paddleWidth)
	{
		posY = paddles[0].posY - ballHeight;
		if (velX == 0 && paddles[0].velX != 0)
		{
			velX = reflection(0, 1);
		}
		velY = -velY;
	}
	if (posY < paddles[1].paddleHeight && posX > paddles[1].posX && posX < paddles[1].posX + paddles[1].paddleWidth)
	{
		posY = paddles[1].paddleHeight;
		if (velX == 0 && paddles[1].velX != 0)
		{
			velX = reflection(1, 1);
		}
		velY = -velY;
	}
	if (posX < paddles[2].paddleWidth && posY > paddles[2].posY 
		&& posY < paddles[2].posY + paddles[2].paddleHeight)
	{
		posX = paddles[2].posX + paddles[2].paddleWidth;
		if (velY == 0 && paddles[2].velY != 0)
		{
			velY = reflection(2, 2);
		}
		velX = -velX;
	}
	if (posX + ballWidth > paddles[3].posX && posY > paddles[3].posY && posY < paddles[3].posY + paddles[3].paddleHeight)
	{
		posX = paddles[3].posX - ballWidth;
	/*	if (velY == 0 && paddles[3].velY != 0)
		{
			velY = reflection(3, 2);
		}
		velX = -velX;*/
		relativeIntersectY = (paddles[3].posY + (paddles[3].paddleHeight / 2)) - (ball.posY + ball.ballHeight/2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[3].paddleHeight / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = BALL_SPEED*cos(bounceAngle);
		velY = BALL_SPEED*-sin(bounceAngle);
	}
	if (posX < paddles[2].paddleWidth || posX > SCREEN_WIDTH - paddles[2].paddleWidth
		|| posY < paddles[0].paddleHeight || posY > SCREEN_HEIGHT - paddles[0].paddleHeight)
	{
		int tmp;
		posX = (SCREEN_WIDTH / 2) - 12;
		posY = (SCREEN_HEIGHT / 2) - 12;
		velX = -BALL_SPEED;
		velY = 0;
		Sleep(750);
	}
}
Event::Event()
{

}
void Event::setPosition(float x, float y, int width, int height)
{
	posX = x;
	posY = y;
	eventWidth = width;
	eventHeight = height;
	inactive = false;
}
void Event::render()
{
	speedTexture.render(posX, posY);
}
int reflection(int index, int type)
{
	if (type == 1)
	{
		if (paddles[index].velX > 0)
		{
			return BALL_SPEED;
		}
		else
		{
			return -BALL_SPEED;
		}
	}
	if (type == 2)
	{
		if (paddles[index].velY > 0)
		{
			return BALL_SPEED;

		}
		else
		{
			return -BALL_SPEED;
		}

	}
}
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}
bool loadSprite()
{
	if (!horizontalPaddle.loadFromFile("paddleH.bmp") || !verticalPaddle.loadFromFile("paddleV.bmp") || !balTexture.loadFromFile("ball.bmp")
		|| !speedTexture.loadFromFile("speed.bmp"))
	{
		return false;
	}
	else
	{
		return true;
	}
}
void close()
{
	horizontalPaddle.free();
	verticalPaddle.free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}
int main(int argc, char* args[])
{
	bool quit = false;
	if (init())
	{
		if (loadSprite())
		{
			SDL_Event event;
			paddles[0].setPosition((SCREEN_WIDTH/2) - 150/2, SCREEN_HEIGHT - 30, 150, 30);
			paddles[1].setPosition((SCREEN_WIDTH/2) - 150/2, 0, 150, 30);
			paddles[2].setPosition(0, (SCREEN_HEIGHT / 2) - 150 / 2, 30, 150);
			paddles[3].setPosition(SCREEN_WIDTH - 30, (SCREEN_HEIGHT / 2) - 150 / 2, 30, 150);
			ball.setPosition((SCREEN_WIDTH / 2) - 12, (SCREEN_HEIGHT / 2) - 12, 24, 24);
			speed.setPosition(600,300,30,30);
			speed.inactive = true;
			while (!quit)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
					handleEvent(event);
				}
				paddles[0].moveHorizontal();
				paddles[1].moveHorizontal();
				paddles[2].moveVertical();
				paddles[3].moveVertical();
				ball.move();
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);
				paddles[0].render(1);
				paddles[1].render(1);
				paddles[2].render(2);
				paddles[3].render(2);
				if (speed.inactive == false)
				{
					speed.render();
				}
				ball.render();
				SDL_RenderPresent(renderer);
			}
		}
	}
	close();

	return 0;
}