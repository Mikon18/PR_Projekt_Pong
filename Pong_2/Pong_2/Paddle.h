#ifndef PADDLE_H_
#define PADDLE_H_

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Paddle
{
public:
	Paddle();
	void setSize(int width, int height);
	void setPosition(float posX, float posY);
	void moveHorizontal();
	void moveVertical();
	float posX, posY;
	int paddleWidth, paddleHeight;
	int velX, velY;
	int index;
};
#endif