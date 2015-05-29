#include "Ball.h"

Ball::Ball()
{
	ballSpeed = -4.0;
	ballWidth = 24;
	ballHeight = 24;
	velX = 0;
	velY = -ballSpeed;
	faultInd = false;
	lastPaddle = 4;
	lastEvent = 0;
	for (int i = 0; i < 4; i++)
	{
		score[i] = 0;
	}
}
void Ball::setPosition(float x, float y)
{
	posX = x;
	posY = y;
}
void Ball::move(Paddle paddles[], Event *speed, Event *reverse, Event *slow, clock_t *start)
{	
	if (posY < speed->posY + speed->eventHeight && posY + ballHeight > speed->posY
		&& posX < speed->posX + speed->eventWidth && posX + ballWidth > speed->posX && speed->inactive == false)
	{
		speed->inactive = true;
		lastEvent = 1;
	}
	if (posY < reverse->posY + reverse->eventHeight && posY + ballHeight > reverse->posY
		&& posX < reverse->posX + reverse->eventWidth && posX + ballWidth > reverse->posX && reverse->inactive == false)
	{
		for (int i = 0; i<4; i++)
		{
			if (i != lastPaddle)
			{
				paddles[i].reverse = true;
			}
		}
		reverse->inactive = true;
		lastEvent = 2;
	}
	if (posY < slow->posY + slow->eventHeight && posY + ballHeight > slow->posY
		&& posX < slow->posX + slow->eventWidth && posX + ballWidth > slow->posX && slow->inactive == false)
	{
		for (int i = 0; i<4; i++)
		{
			if (i != lastPaddle)
			{
				paddles[i].slowDown();
			}
		}
		slow->inactive = true;
		lastEvent = 3;
	}
}