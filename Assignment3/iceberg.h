#ifndef ICEBERGH
#define ICEBERGH
#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "penguinDropping.h"
class iceberg
{
public:
	iceberg(int width, int HEIGHT);
	~iceberg();
	void drawIceberg();
	int getHealth() { return health; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundx() { return boundx; }
	void removeLife() {health--; }
private:
	int health;
	int x;
	int y;
	int boundx;
	ALLEGRO_BITMAP* image;
};
#endif
