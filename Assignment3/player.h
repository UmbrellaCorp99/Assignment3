#ifndef PLAYERH
#define  PLAYERH
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "iceberg.h"
class player
{
public:
	player(int WIDTH, int HEIGHT, iceberg &ice);
	~player();
	void drawPlayer();
	void rotateLeft();
	void rotateRight();
private:
	float angle;
	int x;
	int y;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* image;
};
#endif
