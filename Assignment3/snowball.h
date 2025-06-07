#ifndef SNOWBALLH
#define SNOWBALLH

#include "penguinDropping.h"
#include "player.h"
#include "iceberg.h"
class snowball
{
public:
	snowball();
	~snowball();
	void drawSnowball();
	void fireSnowball(player &pl);
	void updateSnowball(int WIDTH);
	void collideSnowball(penguinDropping pd[], int csize, iceberg &ice);
	//getters and setters for the iceberg class
	bool getLive() { return live; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
private:
	bool live;
	int x;
	int y;
	int boundx;
	int boundy;
	int speed;
	float radian_angle;
	ALLEGRO_SAMPLE* fire;
	ALLEGRO_SAMPLE* hit;
	ALLEGRO_BITMAP* image;
};
#endif
