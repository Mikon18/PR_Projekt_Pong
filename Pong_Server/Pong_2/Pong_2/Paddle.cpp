#include "Paddle.h"

Paddle::Paddle()
{
	velX = 0;
	velY = 0;
	reverse = false;
	paddleVelocity = 6;
}
void Paddle::setSize(int width, int height)
{
	paddleWidth = width;
	paddleHeight = height;
}
void Paddle::setPosition(float x, float y)
{
	posX = x;
	posY = y;
}
void Paddle::slowDown()
{
	paddleVelocity /= 2;
}
void Paddle::moveHorizontal()
{
	posX += velX;
	if (posX < 30)
	{
		posX = 30;
	}
	if(posX + paddleWidth > SCREEN_WIDTH - 30)
	{
		posX = SCREEN_WIDTH - 30 - paddleWidth ;
	}
}
void Paddle::moveVertical()
{
	posY += velY;
	if (posY < 30)
	{
		posY = 30;
	}
	if(posY + paddleHeight > SCREEN_HEIGHT - 30)
	{
		posY =  SCREEN_HEIGHT - 30 - paddleHeight;
	}
}