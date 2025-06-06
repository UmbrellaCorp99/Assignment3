#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <math.h>
#include "snowball.h"

snowball::snowball() {
	image = al_load_bitmap("shotFired.png");
	speed = 5;
	live = false;
	radian_angle = 0;

}
snowball::~snowball() {
	al_destroy_bitmap(image);
}
void snowball::drawSnowball() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}
void snowball::fireSnowball(player &pl) {
	if (!live) {
		x = pl.getX() + pl.getBoundX() / 2;
		y = pl.getY() + pl.getBoundY() / 2;
		radian_angle = ((pl.getAngle() + 64.0) / 0.711) * ((2 * 3.1415) / 360.0);
		live = true;
	}
}
void snowball::updateSnowball(int WIDTH, int HEIGHT) {
	if (live) {
		x -= speed * cos(radian_angle);
		y -= speed * sin(radian_angle);
		if (y < 0) {
			live = false;
		}
	}
}
void snowball::collideSnowball(penguinDropping pd[], int csize) {
	
}
