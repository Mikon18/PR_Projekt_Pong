#include "Pong.h"

Pong::Pong()
{
	window = NULL;
	renderer = NULL;
}
void Pong::randomEvent()
{
	srand(time(NULL));
	int i = rand() % 4 + 1;
	switch (i)
	{
	case 1:
		speed.setPosition(rand() % (SCREEN_WIDTH - 200) + 100, rand() % (SCREEN_HEIGHT - 200) + 100);
		break;
	case 2:
		slow.setPosition(rand() % (SCREEN_WIDTH - 200) + 100, rand() % (SCREEN_HEIGHT - 200) + 100);
		break;
	case 3:
		reverse.setPosition(rand() % (SCREEN_WIDTH - 200) + 100, rand() % (SCREEN_HEIGHT - 200) + 100);
		break;
	}
}
bool Pong::init()
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

bool Pong::loadSprite()
{
	if (!horizontalPaddle.loadFromFile("paddleH.bmp", renderer) || !verticalPaddle.loadFromFile("paddleV.bmp", renderer)
		|| !ballTexture.loadFromFile("ball.bmp", renderer) || !speedTexture.loadFromFile("speed.bmp", renderer)
		|| !reverseTexture.loadFromFile("reverse.bmp", renderer) || !slowTexture.loadFromFile("slow.bmp", renderer))
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Pong::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: 
			if (!paddles[0].reverse)
			{
				paddles[0].velX -= paddles[0].paddleVelocity;
				break;
			}
			else
			{
				paddles[0].velX += paddles[0].paddleVelocity;
				break;
			}
		case SDLK_RIGHT:
			if (!paddles[0].reverse)
			{
				paddles[0].velX += paddles[0].paddleVelocity;
				break;
			}
			else
			{
				paddles[0].velX -= paddles[0].paddleVelocity;
				break;
			}
		case SDLK_a:
			if (!paddles[1].reverse)
			{
				paddles[1].velX -= paddles[1].paddleVelocity;
				break;
			}
			else
			{
				paddles[1].velX += paddles[1].paddleVelocity;
				break;
			}
		case SDLK_d:
			if (!paddles[1].reverse)
			{
				paddles[1].velX += paddles[1].paddleVelocity;
				break;
			}
			else
			{
				paddles[1].velX -= paddles[1].paddleVelocity;
				break;
			}
		case SDLK_i:
			if (!paddles[2].reverse)
			{
				paddles[2].velY -= paddles[2].paddleVelocity;
				break;
			}
			else
			{
				paddles[2].velY += paddles[2].paddleVelocity;
				break;
			}
		case SDLK_k:
			if (!paddles[2].reverse)
			{
				paddles[2].velY += paddles[2].paddleVelocity;
				break;
			}
			else
			{
				paddles[2].velY -= paddles[2].paddleVelocity;
				break;
			}
		case SDLK_y:
			if (!paddles[3].reverse)
			{
				paddles[3].velY -= paddles[3].paddleVelocity;
				break;
			}
			else
			{
				paddles[3].velY += paddles[3].paddleVelocity;
				break;
			}
		case SDLK_h:
			if (!paddles[3].reverse)
			{
				paddles[3].velY += paddles[3].paddleVelocity;
				break;
			}
			else
			{
				paddles[3].velY -= paddles[3].paddleVelocity;
				break;
			}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (!paddles[0].reverse)
			{
				paddles[0].velX += paddles[0].paddleVelocity;
				break;
			}
			else
			{
				paddles[0].velX -= paddles[0].paddleVelocity;
				break;
			}
		case SDLK_RIGHT:
			if (!paddles[0].reverse)
			{
				paddles[0].velX -= paddles[0].paddleVelocity;
				break;
			}
			else
			{
				paddles[0].velX += paddles[0].paddleVelocity;
				break;
			}
		case SDLK_a:
			if (!paddles[1].reverse)
			{
				paddles[1].velX += paddles[1].paddleVelocity;
				break;
			}
			else
			{
				paddles[1].velX -= paddles[1].paddleVelocity;
				break;
			}
		case SDLK_d:
			if (!paddles[1].reverse)
			{
				paddles[1].velX -= paddles[1].paddleVelocity;
				break;
			}
			else
			{
				paddles[1].velX += paddles[1].paddleVelocity;
				break;
			}
		case SDLK_i:
			if (!paddles[2].reverse)
			{
				paddles[2].velY += paddles[2].paddleVelocity;
				break;
			}
			else
			{
				paddles[2].velY -= paddles[2].paddleVelocity;
				break;
			}
		case SDLK_k:
			if (!paddles[2].reverse)
			{
				paddles[2].velY -= paddles[2].paddleVelocity;
				break;
			}
			else
			{
				paddles[2].velY += paddles[2].paddleVelocity;
				break;
			}
		case SDLK_y:
			if (!paddles[3].reverse)
			{
				paddles[3].velY += paddles[3].paddleVelocity;
				break;
			}
			else
			{
				paddles[3].velY -= paddles[3].paddleVelocity;
				break;
			}
		case SDLK_h:
			if (!paddles[3].reverse)
			{
				paddles[3].velY -= paddles[3].paddleVelocity;
				break;
			}
			else
			{
				paddles[3].velY += paddles[3].paddleVelocity;
				break;
			}
		}
	}
}

void Pong::render(Texture texture, int x, int y, SDL_Renderer* renderer)
{
	texture.render(x, y, renderer);
}
void Pong::run()
{
	int tmp;
	bool quit = false;
	clock_t start = clock();
	if (loadSprite())
	{
		SDL_Event event;
		paddles[0].setPosition((SCREEN_WIDTH / 2) - 150 / 2, SCREEN_HEIGHT - 30);
		paddles[1].setPosition((SCREEN_WIDTH / 2) - 150 / 2, 0);
		paddles[2].setPosition(0, (SCREEN_HEIGHT / 2) - 150 / 2);
		paddles[3].setPosition(SCREEN_WIDTH - 30, (SCREEN_HEIGHT / 2) - 150 / 2);
		paddles[0].setSize(150, 30);
		paddles[1].setSize(150, 30);
		paddles[2].setSize(30, 150);
		paddles[3].setSize(30, 150);
		ball.setPosition((SCREEN_WIDTH / 2) - 12, (SCREEN_HEIGHT / 2) - 12);
		speed.inactive = true;
		slow.inactive = true;
		reverse.inactive = true;
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
			tmp = clock();
			if (tmp - start > 5000 && speed.inactive == true && slow.inactive == true
				&& reverse.inactive == true)
			{
				randomEvent();
			}
			paddles[0].moveHorizontal();
			paddles[1].moveHorizontal();
			paddles[2].moveVertical();
			paddles[3].moveVertical();
			ball.move(paddles, &speed, &reverse, &slow, &start);
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			render(horizontalPaddle, paddles[0].posX, paddles[0].posY, renderer);
			render(horizontalPaddle, paddles[1].posX, paddles[1].posY, renderer);
			render(verticalPaddle, paddles[2].posX, paddles[2].posY, renderer);
			render(verticalPaddle, paddles[3].posX, paddles[3].posY, renderer);
			render(ballTexture, ball.posX, ball.posY, renderer);
			if (speed.inactive == false)
			{
				render(speedTexture, speed.posX, speed.posY, renderer);
			}
			if (reverse.inactive == false)
			{
				render(reverseTexture, reverse.posX, reverse.posY, renderer);
			}
			if (slow.inactive == false)
			{
				render(slowTexture, slow.posX, slow.posY, renderer);
			}
			SDL_RenderPresent(renderer);
		}
	}
}