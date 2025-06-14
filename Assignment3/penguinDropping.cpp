#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "penguinDropping.h"

//This is a constructor for the penguinDropping class. Loads an image, a sample, and sets private variables
//Takes no parameters
//No return
penguinDropping::penguinDropping() {
	image = al_load_bitmap("skull150.png");
	injured = al_load_sample("dsoof.wav");
	live = false;
	speed = 5;
	boundx = al_get_bitmap_width(image) * .9;
	boundy = al_get_bitmap_height(image) * .9;
}

//This is a deconstructor for the penguinDropping class
//Takes no parameters
//No return
penguinDropping::~penguinDropping() {
	al_destroy_bitmap(image);
	al_destroy_sample(injured);
}

//This function draws a penguinDropping object at the x and y location
//Takes no parameters
//No return
void penguinDropping::drawPenguin() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}

//This function generates a random x value to spawn a penguinDropping object at, always starts at top of display
//Takes an integer representing the display width as a parameter
//No return
void penguinDropping::startPenguin(int WIDTH) {
	if (!live) {
		if (rand() % 300 == 0) {
			live = true;
			x = rand() % (WIDTH-boundx);
			y = 0;
		}
	}
}

//This function changes the y position of the droppingPenguin, moves downward at a constant rate
//Takes no parameters
//No return
void penguinDropping::updatePenguin() {
	if (live) {
		y += speed;
	}
}

//This function detects if a droppingPenguin touches an iceberg object or if it reaches the bottom of the screen
//Takes an integer representing the display height and an iceberg object
//No return
void penguinDropping::collide(int HEIGHT, iceberg &ice) {
	if (live) {
		if (((x > ice.getX()) && x < (ice.getX() + ice.getBoundx()) ||
			(((x + boundx) > ice.getX()) && ((x + boundx) < (ice.getX() + ice.getBoundx())))) &&
			(y < (ice.getY())) && ((y + boundy) > (ice.getY()))) {
			//if collison occurs with the iceberg, remove a life from the iceberg, set the droppingPenguin live variable to false, and play a sound
			ice.removeLife();
			al_play_sample(injured, 1.4, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			live = false;
		}
		else if ((y + boundy) > HEIGHT) {
			live = false;
		}
	}
}