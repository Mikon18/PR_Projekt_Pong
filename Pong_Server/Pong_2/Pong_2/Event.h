#ifndef EVENT_H_
#define EVENT_H_
class Event
{
public:
	Event();
	void setPosition(float posX, float posY);
	void render();
	float posX, posY;
	bool inactive;
	int eventWidth, eventHeight;
};
#endif