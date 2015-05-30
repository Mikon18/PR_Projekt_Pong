#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include<stdio.h>
#include<winsock2.h>
#include "Texture.h"
#include "Paddle.h"
#include "Ball.h"
#include "Event.h"

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define SERVER "127.0.0.1"
#define BUFLEN 9
#define PORT 8888

class Pong
{
public:
	Pong();
	bool init();
	bool loadSprite();
	void run();
	void render(Texture texture, int x, int y, SDL_Renderer* renderer);
	void handleEvent1(SDL_Event& e);
	void handleEvent2(SDL_Event& e);
	void handleEvent3(SDL_Event& e);
	void handleEvent4(SDL_Event& e);
	void randomEvent();
	SDL_Window* window;
	SDL_Renderer* renderer;
	Texture horizontalPaddle, verticalPaddle, ballTexture, speedTexture, reverseTexture, slowTexture, table[5], keys[2], steeringInstr;
	Paddle paddles[4];
	Ball ball;
	Event speed, reverse, slow;
};