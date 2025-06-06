#ifndef PENGUINDROPPINGH
#define PENGUINDROPPINGH

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

