#ifndef PADDLE_H_
#define PADDLE_H_

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Paddle
{
public:
	Paddle();
	int paddleVelocity;
	void setSize(int width, int height);
	void setPosition(float posX, float posY);
	void moveHorizontal();
	void moveVertical();
	void slowDown();
	int posX, posY;
	int paddleWidth, paddleHeight;
	int velX, velY;
	int index;
	bool reverse; // zmienna okre�laj�ca czy paletka ma odwr�cone kontrole
};
#endif