#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

//This is a constructor for the player class, loads an image for a bitmap and sets private variables
//Takes two integers representing the display width and height, and an iceberg object as parameters
//No return
player::player(int WIDTH, int HEIGHT, iceberg &ice) {
	image = al_load_bitmap("launcher.png");
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	x = (ice.getX() + (ice.getBoundx()/2));
	y = ice.getY() - boundy/2;
	angle = 0;
	
}

//This is a deconstructor for the player class
//Takes no parameters
//No return
player::~player() {
	al_destroy_bitmap(image);
}

//This function draws a rotated player bitmap at the specified x and y position, with the specified angle
//Takes no parameters
//No return
void player::drawPlayer() {
	al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x, y, angle, 0);
}

//This function rotates the player bitmap counterclockwise
//Takes no parameters
//No return
void player::rotateLeft() {
	angle -= 0.1;
	if (angle < -1.05)
	{
		angle = -1.05;
	}
}

//Roatates the player bitmap clockwise
//No parameters
//No return
void player::rotateRight() {
	angle += 0.1;
	
	if (angle > 1.05)
	{
		angle = 1.05;
	}
}