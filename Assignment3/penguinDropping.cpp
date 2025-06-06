#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "penguinDropping.h"

penguinDropping::penguinDropping() {
	image = al_load_bitmap("skull150.png");
	live = false;
	speed = 5;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}
penguinDropping::~penguinDropping() {
	al_destroy_bitmap(image);
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
void penguinDropping::collide(int HEIGHT) {
	if (live) {
		if ((y + boundy) > HEIGHT) {
			live = false;
		}
	}
}