#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h> 
#include <winsock2.h>
#include "Paddle.h"
#include "Ball.h"
#include "Event.h"

#pragma comment(lib,"ws2_32.lib")
#define PORT 8888
#define BUFLEN 9
#define MAX_USERS 4
#pragma warning(disable:4996)
class Pong
{
public:
	Pong();
	void run();
	void randomEvent(int lastEvent);
	Paddle paddles[4];
	Ball ball;
	Event speed, reverse, slow;
};