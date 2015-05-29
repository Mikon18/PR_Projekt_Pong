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
	float bounceAngle;
	float relativeIntersectY, normalizedRelativeIntersectionY;
	posX += velX;
	posY += velY;
	if (faultInd)
	{
		if (posX < 0)
		{
			velX = BALL_SPEED;
			velY = 0;
		}
		if (posY < 0)
		{
			velX = 0;
			velY = BALL_SPEED;
		}
		if (posX + ballWidth > SCREEN_WIDTH)
		{
			velX = -BALL_SPEED;
			velY = 0;
		}
		if (posY + ballHeight > SCREEN_HEIGHT)
		{
			velX = 0;
			velY = -BALL_SPEED;
		}
		posX = (SCREEN_WIDTH / 2) - 12;
		posY = (SCREEN_HEIGHT / 2) - 12;
		lastPaddle = 4;
		ballSpeed = -4.0;
		faultInd = false;
		for(int i = 0; i<4; i++)
		{
			paddles[i].paddleVelocity = 6;
			paddles[i].velX = 0;
			paddles[i].velY = 0;
			paddles[i].reverse = false;
		}
		paddles[0].setPosition((SCREEN_WIDTH / 2) - 150 / 2, SCREEN_HEIGHT - 30);
		paddles[1].setPosition((SCREEN_WIDTH / 2) - 150 / 2, 0);
		paddles[2].setPosition(0, (SCREEN_HEIGHT / 2) - 150 / 2);
		paddles[3].setPosition(SCREEN_WIDTH - 30, (SCREEN_HEIGHT / 2) - 150 / 2);
		speed->inactive = true;
		slow->inactive = true;
		reverse->inactive = true;
	}
	if (posY < speed->posY + speed->eventHeight && posY + ballHeight > speed->posY
		&& posX < speed->posX + speed->eventWidth && posX + ballWidth > speed->posX && speed->inactive == false)
	{
		velX *= 2;
		velY *= 2;
		ballSpeed *= 2;
		lastEvent = 1;
		speed->inactive = true;
		(*start) = clock();
	}
	if (posY < reverse->posY + reverse->eventHeight && posY + ballHeight > reverse->posY
		&& posX < reverse->posX + reverse->eventWidth && posX + ballWidth > reverse->posX && reverse->inactive == false)
	{
		lastEvent = 2;
		reverse->inactive = true;
		(*start) = clock();
	}
	if (posY < slow->posY + slow->eventHeight && posY + ballHeight > slow->posY
		&& posX < slow->posX + slow->eventWidth && posX + ballWidth > slow->posX && slow->inactive == false)
	{
		lastEvent = 3;
		slow->inactive = true;
		(*start) = clock();
	}
	if (posY + ballHeight > paddles[0].posY && posX + ballWidth > paddles[0].posX && posX < paddles[0].posX + paddles[0].paddleWidth)
	{
		posY = paddles[0].posY - ballHeight;
		relativeIntersectY = (paddles[0].posX + (paddles[0].paddleWidth / 2)) - (posX + ballWidth / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[0].paddleWidth / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -ballSpeed*-sin(bounceAngle);
		velY = ballSpeed*cos(bounceAngle);
		lastPaddle = 0;
	}
	if (posY < paddles[1].paddleHeight && posX + ballWidth > paddles[1].posX && posX < paddles[1].posX + paddles[1].paddleWidth)
	{
		posY = paddles[1].paddleHeight;
		relativeIntersectY = (paddles[1].posX + (paddles[1].paddleWidth / 2)) - (posX + ballWidth / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[1].paddleWidth / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -ballSpeed*-sin(bounceAngle);
		velY = -ballSpeed*cos(bounceAngle);
		lastPaddle = 1;
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
		lastPaddle = 2;
	}
	if (posX + ballWidth > paddles[3].posX && posY + ballHeight > paddles[3].posY && posY < paddles[3].posY + paddles[3].paddleHeight)
	{
		posX = paddles[3].posX - ballWidth;
		relativeIntersectY = (paddles[3].posY + (paddles[3].paddleHeight / 2)) - (posY + ballHeight / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[3].paddleHeight / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = ballSpeed*cos(bounceAngle);
		velY = -ballSpeed*-sin(bounceAngle);
		lastPaddle = 3;
	}
	if (posX < 0 || posX + ballWidth > SCREEN_WIDTH
		|| posY < 0 || posY + ballHeight > SCREEN_HEIGHT)
	{
		faultInd = true;

		if (lastPaddle < 4)
		{
			score[lastPaddle]++;
		}
	}
}