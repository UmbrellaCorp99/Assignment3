// Alexander Young
//Assingment 3

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include "penguinDropping.h"
#include "iceberg.h"

int main()
{
    const int FPS = 60;
    int WIDTH = 1280;
    int HEIGHT = 720;
    const int NUM_penguin = 5;
    bool done = false, redraw = false;
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* background = NULL;
    ALLEGRO_BITMAP* logo = NULL;

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


    background = al_load_bitmap("background1280.png");
    logo = al_load_bitmap("Doom_1.png");

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    srand(time(NULL));
    if (!event_queue) {
        al_destroy_bitmap(background);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    penguinDropping penguin[NUM_penguin];
    iceberg myIceberg(WIDTH, HEIGHT);

    //tying event queue to display, timer, and keyboard
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].startPenguin(WIDTH, HEIGHT);
            }
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].updatePenguin();
            }
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].collide(HEIGHT, myIceberg);
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_draw_scaled_bitmap(background, 0, 0, 1280, 800, 0, 0, WIDTH, HEIGHT, 0);
            myIceberg.drawIceberg();
            al_draw_bitmap(logo, WIDTH*.375, 0, 0);
            for (int i = 0; i < NUM_penguin; i++) {
                penguin[i].drawPenguin();
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (myIceberg.getHealth() == 0) {
                done = true;
                al_rest(5);
            }
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(background);
    al_destroy_bitmap(logo);
}


