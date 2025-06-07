#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "iceberg.h"

//This is a constructor for an iceberg, sets the x and y position to a set position relative to the display
//Takes two integers representing the display height and width as parameters
//No return
iceberg::iceberg(int WIDTH, int HEIGHT) {
	image = al_load_bitmap("marble2.jpg");
	health = 5;
	x = WIDTH *.25;
	y = HEIGHT *.85;
	boundx = al_get_bitmap_width(image);
	
	score = 0;
}

//This is a deconstructor for the iceberg class
//Takes no parameters
//No return
iceberg::~iceberg() {
	al_destroy_bitmap(image);
}

//This function draws the iceberg bitmap to the x and y position of the instantiated iceberg
//Takes no parameters
//No return
void iceberg::drawIceberg() {
	al_draw_bitmap(image, x, y, 0);
}
