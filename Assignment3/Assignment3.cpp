// Alexander Young
//Assingment 3
//All sound and visual assets belong to Bethesda Softworks

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "penguinDropping.h"
#include "iceberg.h"
#include "player.h"
#include "snowball.h"

int main()
{
    //variables used throughout main
    const int FPS = 60;
    int WIDTH = 1280;
    int HEIGHT = 720;
    const int NUM_penguin = 5;
    const int NUM_snowballs = 3;
    bool done = false, redraw = false;
    //display, timer, event queue, bitmaps, and audio pointers created
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* background = NULL;
    ALLEGRO_BITMAP* logo = NULL;
    ALLEGRO_BITMAP* base = NULL;
    ALLEGRO_SAMPLE* sample = NULL;
    ALLEGRO_SAMPLE* death = NULL;
    enum KEYS {LEFT, RIGHT, SPACE };
    bool keys[5] = {false, false, false };

    //initializing allegro and addons with error handling
    if (!al_init()) {
        al_show_native_message_box(NULL, "Error", "Allegro failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        al_show_native_message_box(NULL, "Error", "Timer failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    display = al_create_display(WIDTH, HEIGHT);
    if (!display) {
        al_show_native_message_box(NULL, "Error", "Display failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        return -1;
    }
    al_init_image_addon();
    if (!al_init_image_addon()) {
        al_show_native_message_box(NULL, "Error", "Display failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_install_audio();
    if (!al_install_audio) {
        al_show_native_message_box(NULL, "Error", "Audio failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_init_acodec_addon();
    if (!al_init_acodec_addon()) {
        al_show_native_message_box(NULL, "Error", "Acodec failed to initialize", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if (!al_reserve_samples(14)) {
        exit(9);
    }

    //loading two samples to play, one for bg music and one for game over
    sample = al_load_sample("03. E1M1 - At Doom's Gate.mp3");
    death = al_load_sample("dspldeth.wav");

    //background, logo, and cannon base bitmaps
    background = al_load_bitmap("background1280.png");
    logo = al_load_bitmap("Doom_1.png");
    base = al_load_bitmap("launcherBase.png");

    //setting up event queue and fonts
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    srand(time(NULL));
    if (!event_queue) {
        al_destroy_bitmap(background);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT* gameplayFont = al_load_font("Doom2016Left-RpJDA.ttf", 32, 0);
    ALLEGRO_FONT* endFont = al_load_font("Doom2016Left-RpJDA.ttf", 128, 0);

    //instantiating dropppingPenguin objects, snowball objects, a player, and an iceberg
    penguinDropping penguin[NUM_penguin];
    iceberg myIceberg(WIDTH, HEIGHT);
    player myPlayer(WIDTH, HEIGHT, myIceberg);
    snowball MySnowball[5];

    //tying event queue to display, timer, and keyboard
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    //start the timer and start playing bg music on a loop
    al_start_timer(timer);
    al_play_sample(sample, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //The next thing in the queue is a timer event
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            if (keys[LEFT])
                myPlayer.rotateLeft();
            if (keys[RIGHT])
                myPlayer.rotateRight();
            //fire snowball if spacebar is pressed (holding spacebar will continue to call it subsequently) 
            if(keys[SPACE])
                for (int i = 0; i < NUM_snowballs; i++) {
                    MySnowball[i].fireSnowball(myPlayer);
                }
            //change the current x and y position of a fired snowball
            for (int i = 0; i < NUM_snowballs; i++) {
                MySnowball[i].updateSnowball(WIDTH);
            }
            //generate the x and y pos for a new droppingPenguin
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].startPenguin(WIDTH);
            }
            //change the current x and y pos of all live droppingPenguin
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].updatePenguin();
            }
            //check to see if a snowball touches a droppingPenguin
            for (int i = 0; i < NUM_snowballs; i++) {
                MySnowball[i].collideSnowball(penguin, NUM_penguin, myIceberg);
            }
            //check to see if a droppingPenguin touches the iceberg
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].collide(HEIGHT, myIceberg);
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        //next two if statements check for keyboard input
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }
        //if event queue is empty, draw new bitmaps at updated locations
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_draw_scaled_bitmap(background, 0, 0, 1280, 800, 0, 0, WIDTH, HEIGHT, 0);
            myIceberg.drawIceberg();
            for (int i = 0; i < NUM_snowballs; i++) {
                MySnowball[i].drawSnowball();
            }
            myPlayer.drawPlayer();
            al_draw_textf(gameplayFont, al_map_rgb(255, 255, 0), WIDTH * .2, HEIGHT * .1, 0, "Score: %i", myIceberg.getScore());
            al_draw_textf(gameplayFont, al_map_rgb(255, 255, 0), WIDTH * .7, HEIGHT * .1, 0, "Health: %i", myIceberg.getHealth());
            al_draw_bitmap(base, (myIceberg.getX() + (myIceberg.getBoundx() / 2)) - (al_get_bitmap_width(base)/2), myIceberg.getY() - al_get_bitmap_height(base), 0 );
            al_draw_bitmap(logo, WIDTH*.375, 0, 0);
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].drawPenguin();
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //if iceberg health reaches 0, play audio and print messages
            if (myIceberg.getHealth() == 0) {
                al_draw_text(endFont, al_map_rgb(255, 255, 0), WIDTH*.4, HEIGHT*.3, 0, "YOU DIED");
                al_draw_textf(endFont, al_map_rgb(255, 255, 0), WIDTH * .33, HEIGHT*.5, 0, "Final Score: %i", myIceberg.getScore());
                al_draw_text(gameplayFont, al_map_rgb(255, 255, 0), WIDTH/2, HEIGHT * .9, ALLEGRO_ALIGN_CENTER, "All visual and audio assets belong to Bethesda Softworks");
                al_play_sample(death, .6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                al_flip_display();
                al_rest(5);
                done = true;
            }
        }
    }
    //clear up memory by destroying the pointers
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(background);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(base);
    al_destroy_font(gameplayFont);
    al_destroy_sample(sample);
    al_destroy_sample(death);
    al_destroy_font(endFont);
}


