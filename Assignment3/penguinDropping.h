#ifndef PENGUINDROPPINGH
#define PENGUINDROPPINGH
#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "iceberg.h"
class penguinDropping
{
public:
	penguinDropping();
	~penguinDropping();
	void drawPenguin();
	void startPenguin(int WIDTH, int HEIGHT);
	void updatePenguin();
	int getX() { return x; }
	int getY() { return y; }
	int getBoundx() { return boundx; }
	int getBoundy() { return boundy; }
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
	void collide(int HEIGHT, iceberg &ice);
private:
	bool live;
	int x;
	int y;
	int boundx;
	int boundy;
	int speed;
	ALLEGRO_BITMAP* image;
};
#endif

