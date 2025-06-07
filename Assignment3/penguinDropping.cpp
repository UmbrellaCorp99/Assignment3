#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "penguinDropping.h"

penguinDropping::penguinDropping() {
	image = al_load_bitmap("skull150.png");
	injured = al_load_sample("dsoof.wav");
	live = false;
	speed = 5;
	boundx = al_get_bitmap_width(image) * .9;
	boundy = al_get_bitmap_height(image) * .9;
}
penguinDropping::~penguinDropping() {
	al_destroy_bitmap(image);
	al_destroy_sample(injured);
}
void penguinDropping::drawPenguin() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}
void penguinDropping::startPenguin(int WIDTH, int HEIGHT) {
	if (!live) {
		if (rand() % 300 == 0) {
			live = true;
			x = rand() % (WIDTH-boundx);
			y = 0;
		}
	}
}
void penguinDropping::updatePenguin() {
	if (live) {
		y += speed;
	}
}
void penguinDropping::collide(int HEIGHT, iceberg &ice) {
	if (live) {
		if (((x > ice.getX()) && x < (ice.getX() + ice.getBoundx()) ||
			(((x + boundx) > ice.getX()) && ((x + boundx) < (ice.getX() + ice.getBoundx())))) &&
			(y < (ice.getY())) && ((y + boundy) > (ice.getY()))) {
			ice.removeLife();
			al_play_sample(injured, 1.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			live = false;
		}
		else if ((y + boundy) > HEIGHT) {
			live = false;
		}
	}
}