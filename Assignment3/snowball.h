#pragma once
#include "penguinDropping.h"
class snowball
{
public:
	snowball();
	~snowball();
	void drawSnowball();
	void fireSnowball();
	void updateSnowball();
	void collideSnowball(penguinDropping pd[], int csize);
	bool getLive() { return live; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundx() { return boundx; }
	int getBoundy() { return boundy; }
private:
	bool live;
	int x;
	int y;
	int boundx;
	int boundy;
	int speed;
};

