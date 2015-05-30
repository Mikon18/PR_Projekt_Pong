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
				if (TTF_Init() == -1)
				{
					success = false;
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
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
void Pong::handleEvent1(SDL_Event& e)
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
		}
	}
}

void Pong::handleEvent2(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: 
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
		case SDLK_RIGHT:
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
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
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
		case SDLK_RIGHT:
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
		}
	}
}
void Pong::handleEvent3(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
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
		case SDLK_DOWN:
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
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
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
		case SDLK_DOWN:
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
		}
	}
}
void Pong::handleEvent4(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
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
		case SDLK_DOWN:
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
		case SDLK_UP:
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
		case SDLK_DOWN:
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
	/*SDL*/
	bool quit = false;
	clock_t start = clock();
	SDL_Color textColor = { 0, 0, 0 };
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
	int ballXtmp;
	int ballYtmp;
	/*Sockety*/
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	int buf[BUFLEN];
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	int recv_len = 0;
	int id = -1;
	///////////////////////////////////////
	if (loadSprite())
	{
		while (!quit)
		{
			SDL_Event event;
			if (id == -1)
			{
				if ((recv_len = recvfrom(s, (char*)buf, BUFLEN*sizeof(int), 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
				{
					buf[0] = -1;
					if (sendto(s, (char*)buf, BUFLEN * sizeof(int), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
					{
					}
				}
				else
				{
					id = buf[0];
				}
			}
			else
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
					switch (id)
					{
					case 0:
						handleEvent1(event);
						break;
					case 1:
						handleEvent2(event);
						break;
					case 2:
						handleEvent3(event);
						break;
					case 3:
						handleEvent4(event);
						break;
					}
				}
				if (id >= 2)
				{
					paddles[id].moveVertical();
				}
				else
				{
					paddles[id].moveHorizontal();
				}
				buf[0] = id;
				if (id > 1)
				{
					buf[1] = paddles[id].posY;
				}
				else
				{
					buf[1] = paddles[id].posX;
				}

				if (sendto(s, (char*)buf, BUFLEN * sizeof(int), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
				{
				}
				if ((recv_len = recvfrom(s, (char*)buf, BUFLEN*sizeof(int), 0, (struct sockaddr *) &si_other, &slen)) != SOCKET_ERROR)
				{
					paddles[0].posX = buf[0];
					paddles[1].posX = buf[1];
					paddles[2].posY = buf[2];
					paddles[3].posY = buf[3];
					ballXtmp = ball.posX;
					ballYtmp = ball.posY;
					ball.posX = buf[4];
					ball.posY = buf[5];
					if (ball.lastEvent != buf[6])
					{
						switch (buf[6])
						{
						case 1:
							speed.inactive = false;
							speed.posX = buf[7];
							speed.posY = buf[8];
							break;
						case 3:
							slow.inactive = false;
							slow.posX = buf[7];
							slow.posY = buf[8];
							break;
						case 2:
							reverse.inactive = false;
							reverse.posX = buf[7];
							reverse.posY = buf[8];
							break;
						}
					}
					ball.move(paddles, &speed, &reverse, &slow, &start);
					if ((abs(ball.posX - ballXtmp) > 200 || abs(ball.posY - ballYtmp) > 200) && ball.posX != -200)
					{
						ballXtmp = ball.posX;
						ballYtmp = ball.posY;
						ball.faultInd = true;
						if (ball.lastPaddle < 4)
						{
							ball.score[ball.lastPaddle]++;
						}
					}
				}
			}
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
			if (ball.posX == -200)
			{
				steeringInstr.loadFromRenderedText("Your controls: ", textColor, renderer);
				switch (id)
				{
				case 0:
					keys[0].loadFromFile("lewo.bmp", renderer);
					keys[1].loadFromFile("prawo.bmp", renderer);
					render(steeringInstr, 310, 420, renderer);
					render(keys[0], 325, 500, renderer);
					render(keys[1], 426, 500, renderer);
					break;
				case 1:
					keys[0].loadFromFile("lewo.bmp", renderer);
					keys[1].loadFromFile("prawo.bmp", renderer);
					render(steeringInstr, 310, 50, renderer);
					render(keys[0], 325, 130, renderer);
					render(keys[1], 426, 130, renderer);
					break;
				case 2:
					keys[0].loadFromFile("gora.bmp", renderer);
					keys[1].loadFromFile("dol.bmp", renderer);
					render(steeringInstr, 80, 225, renderer);
					render(keys[0], 130, 275, renderer);
					render(keys[1], 130, 325, renderer);
					break;
				case 3:
					keys[0].loadFromFile("gora.bmp", renderer);
					keys[1].loadFromFile("dol.bmp", renderer);
					render(steeringInstr, 575, 225, renderer);
					render(keys[0], 625, 275, renderer);
					render(keys[1], 625, 325, renderer);
					break;
				}
			}
			if (ball.faultInd)
			{
				table[0].loadFromRenderedText("Score:", textColor, renderer);
				table[1].loadFromRenderedText("Bottom Paddle: " + to_string(ball.score[0]), textColor, renderer);
				table[2].loadFromRenderedText("Top    Paddle: " + to_string(ball.score[1]), textColor, renderer);
				table[3].loadFromRenderedText("Left   Paddle: " + to_string(ball.score[2]), textColor, renderer);
				table[4].loadFromRenderedText("Right  Paddle: " + to_string(ball.score[3]), textColor, renderer);
				render(table[0], 300, 225, renderer);
				render(table[1], 300, 255, renderer);
				render(table[2], 300, 285, renderer);
				render(table[3], 300, 315, renderer);
				render(table[4], 300, 345, renderer);
			}
			SDL_RenderPresent(renderer);
			if (ball.faultInd)
			{
				Sleep(2000);
				ball.faultInd = false;
			}
		}
		
	}
	closesocket(s);
	WSACleanup();
}