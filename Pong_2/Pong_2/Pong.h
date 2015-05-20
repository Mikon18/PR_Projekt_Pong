#include <SDL.h>
#include "Texture.h"
#include "Paddle.h"
#include "Ball.h"
#include "Event.h"
const int PADDLE_VELOCITY = 6;

class Pong
{
public:
	Pong();
	bool init();
	bool loadSprite();
	void run();
	void render(Texture texture, int x, int y, SDL_Renderer* renderer);
	void handleEvent(SDL_Event& e);
	SDL_Window* window;
	SDL_Renderer* renderer;
	Texture horizontalPaddle, verticalPaddle, ballTexture, speedTexture;
	Paddle paddles[4];
	Ball ball;
	Event speed;
};