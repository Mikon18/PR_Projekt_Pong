#include "Ball.h"

Ball::Ball()
{
	ballSpeed = -4.0;
	ballWidth = 24;
	ballHeight = 24;
	velX = 0;
	velY = -ballSpeed;
}
void Ball::setPosition(float x, float y)
{
	posX = x;
	posY = y;
}
void Ball::move(Paddle paddles[], Event *speed, Event *reverse, Event *slow, clock_t *start)
{
	float bounceAngle;
	float relativeIntersectY, normalizedRelativeIntersectionY;
	posX += velX;
	posY += velY;
	if (posY < speed->posY + speed->eventHeight && posY + ballHeight > speed->posY
		&& posX < speed->posX + speed->eventWidth && posX + ballWidth > speed->posX && speed->inactive == false)
	{
		velX *= 2;
		velY *= 2;
		ballSpeed *= 2;
		speed->inactive = true;
		*(start) = clock();
	}
	if (posY < reverse->posY + reverse->eventHeight && posY + ballHeight > reverse->posY
		&& posX < reverse->posX + reverse->eventWidth && posX + ballWidth > reverse->posX && reverse->inactive == false)
	{
		for (int i = 0; i<4; i++)
		{
			if (i != lastPlayer)
			{
				paddles[i].reverse = true;
			}
		}
		reverse->inactive = true;
		*(start) = clock();
	}
	if (posY < slow->posY + slow->eventHeight && posY + ballHeight > slow->posY
		&& posX < slow->posX + slow->eventWidth && posX + ballWidth > slow->posX && slow->inactive == false)
	{
		for (int i = 0; i<4; i++)
		{
			if (i != lastPlayer)
			{
				paddles[i].slowDown();
			}
		}
		slow->inactive = true;
		*(start) = clock();
	}
	if (posY + ballHeight > paddles[0].posY && posX + ballWidth > paddles[0].posX && posX < paddles[0].posX + paddles[0].paddleWidth)
	{
		posY = paddles[0].posY - ballHeight;
		relativeIntersectY = (paddles[0].posX + (paddles[0].paddleWidth / 2)) - (posX + ballWidth / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[0].paddleWidth / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -ballSpeed*-sin(bounceAngle);
		velY = ballSpeed*cos(bounceAngle);
		lastPlayer = 0;
	}
	if (posY < paddles[1].paddleHeight && posX + ballWidth > paddles[1].posX && posX < paddles[1].posX + paddles[1].paddleWidth)
	{
		posY = paddles[1].paddleHeight;
		relativeIntersectY = (paddles[1].posX + (paddles[1].paddleWidth / 2)) - (posX + ballWidth / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[1].paddleWidth / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -ballSpeed*-sin(bounceAngle);
		velY = -ballSpeed*cos(bounceAngle);
		lastPlayer = 1;
	}
	if (posX < paddles[2].paddleWidth && posY + ballHeight > paddles[2].posY
		&& posY < paddles[2].posY + paddles[2].paddleHeight)
	{
		posX = paddles[2].posX + paddles[2].paddleWidth;
		relativeIntersectY = (paddles[2].posY + (paddles[2].paddleHeight / 2)) - (posY + ballHeight / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[2].paddleHeight / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -ballSpeed*cos(bounceAngle);
		velY = -ballSpeed*-sin(bounceAngle);
		lastPlayer = 2;
	}
	if (posX + ballWidth > paddles[3].posX && posY + ballHeight > paddles[3].posY && posY < paddles[3].posY + paddles[3].paddleHeight)
	{
		posX = paddles[3].posX - ballWidth;
		relativeIntersectY = (paddles[3].posY + (paddles[3].paddleHeight / 2)) - (posY + ballHeight / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[3].paddleHeight / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = ballSpeed*cos(bounceAngle);
		velY = -ballSpeed*-sin(bounceAngle);
		lastPlayer = 3;
	}
	if (posX < 0 || posX + ballWidth > SCREEN_WIDTH
		|| posY < 0 || posY + ballHeight > SCREEN_HEIGHT)
	{
		int tmp;
		posX = (SCREEN_WIDTH / 2) - 12;
		posY = (SCREEN_HEIGHT / 2) - 12;
		ballSpeed = BALL_SPEED;
		velX = -ballSpeed;
		velY = 0;
		Sleep(750);
	}
}