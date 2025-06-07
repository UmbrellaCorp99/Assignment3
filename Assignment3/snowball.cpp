#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <math.h>
#include "snowball.h"

snowball::snowball() {
	image = al_load_bitmap("shotFired.png");
	speed = 10;
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
		x = pl.getX();
		y = pl.getY();
		radian_angle = -pl.getAngle() + 1.57;
		live = true;
	}
}
void snowball::updateSnowball(int WIDTH) {
	if (live) {
		x += speed * cos(radian_angle);
		y -= speed * sin(radian_angle);
		if (y < 0 || x > WIDTH || x < 0) {
			live = false;
		}
	}
}
void snowball::collideSnowball(penguinDropping pd[], int csize, iceberg &ice) {
	if (live) {
		for (int j = 0; j < csize; j++) {
			if(pd[j].getLive()){
				if (x > (pd[j].getX() - pd[j].getBoundx()) &&
					x < (pd[j].getX() + pd[j].getBoundx()) &&
					y >(pd[j].getY() - pd[j].getBoundy()) &&
					y < (pd[j].getY() + pd[j].getBoundy()))
				{
					live = false;
					pd[j].setLive(false);
					ice.updateScore();
				}
			}
		}
	}
}
