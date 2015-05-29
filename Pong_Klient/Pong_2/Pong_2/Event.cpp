#include "Event.h"

Event::Event()
{
	eventWidth = 30;
	eventHeight = 30;

}
void Event::setPosition(float x, float y)
{
	posX = x;
	posY = y;
	inactive = false;
}