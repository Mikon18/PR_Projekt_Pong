#include "Paddle.h"

Paddle::Paddle()
{
	velX = 0;
	velY = 0;
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