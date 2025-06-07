#ifndef PLAYERH
#define  PLAYERH

#include "iceberg.h"
class player
{
public:
	player(int WIDTH, int HEIGHT, iceberg &ice);
	~player();
	void drawPlayer();
	void rotateLeft();
	void rotateRight();
	//getters and setters for the player class
	float getAngle() { return angle; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
private:
	float angle;
	int x;
	int y;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* image;
};
#endif
