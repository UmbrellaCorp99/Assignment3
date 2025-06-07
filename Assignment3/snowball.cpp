#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include "snowball.h"

snowball::snowball() {
	image = al_load_bitmap("shotFired.png");
	fire = al_load_sample("dsrlaunc.wav");
	hit = al_load_sample("dsbarexp.wav");
	speed = 10;
	live = false;
	radian_angle = 0;

}
snowball::~snowball() {
	al_destroy_bitmap(image);
	al_destroy_sample(fire);
	al_destroy_sample(hit);

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
		al_play_sample(fire, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
				if ((((y > pd[j].getY()) && y < (pd[j].getY() + pd[j].getBoundy()) ||
					(((y + boundy) > pd[j].getY()) && ((y + boundy) < (pd[j].getY() + pd[j].getBoundy())))) &&
					(x > (pd[j].getX())) && (x < (pd[j].getX() + pd[j].getBoundy()))) || (((y > pd[j].getY()) && y < (pd[j].getY() + pd[j].getBoundy()) ||
						(((y + boundy) > pd[j].getY()) && ((y + boundy) < (pd[j].getY() + pd[j].getBoundy())))) &&
						(x < pd[j].getX()) && ((x + boundx) > (pd[j].getX()))) || (((x > pd[j].getX()) && x < (pd[j].getX() + pd[j].getBoundy()) ||
							(((x + boundx) > pd[j].getX()) && ((x + boundx) < (pd[j].getX() + pd[j].getBoundx())))) &&
							(y > pd[j].getY()) && (y < (pd[j].getY() + pd[j].getBoundy()))))
				{
					live = false;
					pd[j].setLive(false);
					ice.updateScore();
					al_play_sample(hit, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
		}
	}
}
