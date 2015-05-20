#include "Ball.h"

Ball::Ball()
{
	ballWidth = 24;
	ballHeight = 24;
	velX = -BALL_SPEED;
	velY = 0;
}
void Ball::setPosition(float x, float y)
{
	posX = x;
	posY = y;
}
void Ball::move(Paddle paddles[], Event speed)
{
	float bounceAngle;
	float relativeIntersectY, normalizedRelativeIntersectionY;
	posX += velX;
	posY += velY;
	if (posY < speed.posY + speed.eventHeight && posY + ballHeight > speed.posY
		&& posX < speed.posX + speed.eventWidth && posX + ballWidth > speed.posX && speed.inactive == false)
	{
		velX *= 2;
		velY *= 2;
		speed.inactive = true;
	}
	if (posY + ballHeight > paddles[0].posY && posX + ballWidth > paddles[0].posX && posX < paddles[0].posX + paddles[0].paddleWidth)
	{
		posY = paddles[0].posY - ballHeight;
		relativeIntersectY = (paddles[0].posX + (paddles[0].paddleWidth / 2)) - (posX + ballWidth / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[0].paddleWidth / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -BALL_SPEED*-sin(bounceAngle);
		velY = BALL_SPEED*cos(bounceAngle);
	}
	if (posY < paddles[1].paddleHeight && posX + ballWidth > paddles[1].posX && posX < paddles[1].posX + paddles[1].paddleWidth)
	{
		posY = paddles[1].paddleHeight;
		relativeIntersectY = (paddles[1].posX + (paddles[1].paddleWidth / 2)) - (posX + ballWidth / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[1].paddleWidth / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -BALL_SPEED*-sin(bounceAngle);
		velY = -BALL_SPEED*cos(bounceAngle);
	}
	if (posX < paddles[2].paddleWidth && posY + ballHeight > paddles[2].posY
		&& posY < paddles[2].posY + paddles[2].paddleHeight)
	{
		posX = paddles[2].posX + paddles[2].paddleWidth;
		relativeIntersectY = (paddles[2].posY + (paddles[2].paddleHeight / 2)) - (posY + ballHeight / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[2].paddleHeight / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = -BALL_SPEED*cos(bounceAngle);
		velY = -BALL_SPEED*-sin(bounceAngle);
	}
	if (posX + ballWidth > paddles[3].posX && posY + ballHeight > paddles[3].posY && posY < paddles[3].posY + paddles[3].paddleHeight)
	{
		posX = paddles[3].posX - ballWidth;
		relativeIntersectY = (paddles[3].posY + (paddles[3].paddleHeight / 2)) - (posY + ballHeight / 2);
		normalizedRelativeIntersectionY = (relativeIntersectY / (paddles[3].paddleHeight / 2));
		bounceAngle = normalizedRelativeIntersectionY * MAX_BOUND_ANGLE;
		velX = BALL_SPEED*cos(bounceAngle);
		velY = -BALL_SPEED*-sin(bounceAngle);
	}
	if (posX < 0 || posX + ballWidth > SCREEN_WIDTH
		|| posY < 0 || posY + ballHeight > SCREEN_HEIGHT)
	{
		int tmp;
		posX = (SCREEN_WIDTH / 2) - 12;
		posY = (SCREEN_HEIGHT / 2) - 12;
		velX = -BALL_SPEED;
		velY = 0;
		Sleep(750);
	}
}