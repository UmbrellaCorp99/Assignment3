#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include "snowball.h"

//This is a constructor for the snowball class. Loads an image as a bitmap, loads two samples, and sets private variables
//Takes no parametesr
//No return
snowball::snowball() {
	image = al_load_bitmap("shotFired.png");
	fire = al_load_sample("dsrlaunc.wav");
	hit = al_load_sample("dsbarexp.wav");
	speed = 10;
	live = false;
	radian_angle = 0;

}

//This is a deconstructor for the snowball class
//Takes no parameters
//No return
snowball::~snowball() {
	al_destroy_bitmap(image);
	al_destroy_sample(fire);
	al_destroy_sample(hit);

}

//This function draws a snowball bitmap at the x and y location
//Takes no parameters
//No return
void snowball::drawSnowball() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}

//This function sets a snowball state to true and generates a starting x and y location, as well as the angle at which the player was aiming at the time of calling the function
//Takes a player object as a parameter
//No return
void snowball::fireSnowball(player &pl) {
	if (!live) {
		x = pl.getX();
		y = pl.getY();
		radian_angle = -pl.getAngle() + 1.57;
		live = true;
		//plays a sound upon live being set to true
		al_play_sample(fire, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

//This function changes the x and y location of all live snowballs or despawns it if it reaches the display boundary
//Takes an integer representing the display width as a parameter
//No return
void snowball::updateSnowball(int WIDTH) {
	if (live) {
		x += speed * cos(radian_angle);
		y -= speed * sin(radian_angle);
		if (y < 0 || x > WIDTH || x < 0) {
			live = false;
		}
	}
}

//This function detects if a snowball touches a droppingPenguin object
//Takes an array of penguinDropping objects, the number of droppingPenguins, and an iceberg object at parameters
//No return
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
					//if a collision occures, set droppingPenguin and snowball to false, upadte the iceberg score, and play a sound
					live = false;
					pd[j].setLive(false);
					ice.updateScore();
					al_play_sample(hit, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
		}
	}
}
