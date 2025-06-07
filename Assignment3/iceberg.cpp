#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "iceberg.h"

iceberg::iceberg(int WIDTH, int HEIGHT) {
	image = al_load_bitmap("marble2.jpg");
	health = 5;
	x = WIDTH *.25;
	y = HEIGHT *.85;
	boundx = al_get_bitmap_width(image);
	score = 0;
}
iceberg::~iceberg() {
	al_destroy_bitmap(image);
}
void iceberg::drawIceberg() {
	al_draw_bitmap(image, x, y, 0);
}
