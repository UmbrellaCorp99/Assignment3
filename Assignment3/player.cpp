#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::player(int WIDTH, int HEIGHT, iceberg &ice) {
	image = al_load_bitmap("launcher.png");
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	x = (ice.getX() + (ice.getBoundx()/2));
	y = ice.getY() - boundy/2;
	angle = 0;
	
}
player::~player() {
	al_destroy_bitmap(image);
}
void player::drawPlayer() {
	al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x, y, angle, 0);
}
void player::rotateLeft() {
	angle += 0.8;
}
void player::rotateRight() {
	angle -= 0.8;
}