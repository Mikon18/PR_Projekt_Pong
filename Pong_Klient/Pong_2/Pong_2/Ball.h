#include "Paddle.h"
#include "Event.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#ifndef BALL_H_
#define BALL_H_
const float BALL_SPEED = -10.0;
const float MAX_BOUND_ANGLE = 5 * M_PI / 12;

class Ball
{
public:
	float ballSpeed;
	Ball();
	void setPosition(float posX, float posY);
	void move(Paddle paddles[], Event *speed, Event *reverse, Event *slow, clock_t *start);
	float posX, posY;
	float velX, velY;
	bool faultInd;
	int lastPaddle, score[4];
	int lastEvent;
	int ballWidth, ballHeight;
};
#endif