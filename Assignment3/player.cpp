#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::player(int WIDTH, int HEIGHT, iceberg &ice) {
	image = al_load_bitmap("launcher.png");
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	x = (ice.getX() + (ice.getBoundx()/2) - boundx/2);
	y = ice.getY() - boundy;
	
}
player::~player() {
	al_destroy_bitmap(image);
}
void player::drawPlayer() {
	al_draw_bitmap(image, x, y, 0);
}