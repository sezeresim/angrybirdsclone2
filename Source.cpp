/*

Sezer Esim
sezeresim@gmail.com

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>


//global variables
float velocityy = NULL;
float velocityx = NULL;


int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;

	srand(time(NULL));
	const float FPS = 60.0;

	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();


	ALLEGRO_EVENT_QUEUE *event = NULL;
	ALLEGRO_TIMER *timer = NULL;;
	ALLEGRO_FONT *mainfont_20 = NULL, *mainfont_25 = NULL, *mainfont_30 = NULL, *mainfont_35 = NULL, *mainfont_40 = NULL;
	ALLEGRO_BITMAP *backround1 = NULL, *sling = NULL, *box = NULL, *gamewin = NULL, *gameend = NULL,*menuscreen=NULL,*star=NULL,*playagainbutton=NULL,*icon=NULL;
	ALLEGRO_BITMAP *bird = NULL;
	ALLEGRO_SAMPLE *soundeffect = NULL, *sound = NULL;

	//fonts
	mainfont_20 = al_load_ttf_font("fonts/mainfont.TTF", 20, 2);
	mainfont_25 = al_load_ttf_font("fonts/mainfont.TTF", 25, 2);
	mainfont_30 = al_load_ttf_font("fonts/mainfont.TTF", 30, 2);
	mainfont_35 = al_load_ttf_font("fonts/mainfont.TTF", 35, 2);
	mainfont_40 = al_load_ttf_font("fonts/mainfont.TTF", 40, 2);


	//images
	backround1 = al_load_bitmap("images/backround.png");
	sling = al_load_bitmap("images/sling.png");
	box = al_load_bitmap("images/box.png");
	gamewin = al_load_bitmap("images/gamewin.png");
	gameend = al_load_bitmap("images/gameend.png");
	menuscreen = al_load_bitmap("images/menu.png");
	star = al_load_bitmap("images/star.png");
	playagainbutton= al_load_bitmap("images/playagain.png");
	icon = al_load_bitmap("images/icon.png");
	bird = al_load_bitmap("images/bird.png");


	//sounds
	soundeffect = al_load_sample("music/music.wav");
	sound = al_load_sample("music/music2.wav");


	//sounds settings
	ALLEGRO_SAMPLE_INSTANCE *songinstance = al_create_sample_instance(sound);
	al_reserve_samples(2);
	al_set_sample_instance_playmode(songinstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songinstance, al_get_default_mixer());


	//other things
	timer = al_create_timer(0.5 / FPS);
	display = al_create_display(900, 600);
	event = al_create_event_queue();
	al_start_timer(timer);
	al_play_sample_instance(songinstance);


	al_register_event_source(event, al_get_mouse_event_source());
	al_unregister_event_source(event, al_get_display_event_source(display));
	al_register_event_source(event, al_get_keyboard_event_source());
	al_register_event_source(event, al_get_timer_event_source(timer));

	//window icon
	al_set_display_icon(display, icon);


	//variable
	bool done = false;
	float move_speed = 10;
	float x = NULL, y = NULL;
	float vx =NULL, vy = NULL;
	int score = 0, shootcount = 3, shootcount2 = 3, starcount = 0;
	bool box1 = true, box2 = true, box3 = true;
	bool gameover = false;
	int playagain = 1;
	bool  draw2 = false;
	bool menu = true;
	int fourclick = 4;
	int point1, point2;
	int total;

	//math processing
	float cospoint;
	float sinpoint;
	float acceleration;
	float time;
	

	while (!done) {


		ALLEGRO_EVENT even_01;
		al_wait_for_event(event, &even_01);

		bool draw = true;
		
		//border of sling
		point1 = x - 225, point2 = y - 160;;
		total = point1*point1 + point2*point2;


		//mause controller
		if (even_01.type == ALLEGRO_EVENT_MOUSE_AXES)//axes of mouse
		{
			x = even_01.mouse.x;
			y = even_01.mouse.y;
		}
		else if (even_01.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP  )
		{



			//shoting
			if (menu == false && total<50000) {

				vx = x, vy = y;

				//border of sling
				point1 = vx - 225;
				point2 = vy - 210;;
				total = point1*point1 + point2*point2;

				//math processing
				cospoint = ((225 - vx) / (sqrt(total)));
				sinpoint = ((210 - vy) / (sqrt(total)));
				velocityx = (sqrt(total))*cospoint;
				velocityy = (float)(sqrt(total))*sinpoint;

				draw2 = true;
				shootcount--;
				shootcount2--;
				fourclick--;
				if (shootcount < 0) {
					shootcount = 0;
				}
					
				//for score
				if (gameover == false) {
					starcount++;
					if (starcount > 3) {
						starcount = 3;
					}
				}

			}


			//menuscreen
			if (menu == true) {

				if (y < 215 && y>133 && x < 586 && x>285) {
					menu = false;
				}
				else if (y < 297 && y>215 && x < 586 && x>227) {

					done = true;
				}

			}
				
		}
	
		 
		//escape and play again
		if (even_01.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (even_01.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_F5:
				if (playagain == 0) {

					// reset variable or playagain with F5
					x = NULL, y = NULL;
					vx = NULL, vy = NULL;
					score = 0, shootcount = 3, shootcount2 = 3, starcount = 0;
					box1 = true, box2 = true, box3 = true;
					gameover = false;
					playagain = 1;
					draw2 = false;
					menu = true;
					fourclick = 4;
				}
				break;
					
			}
		}
		

		//math processing of shoting
		acceleration =80;
		time = 0.02;
		velocityy = velocityy + acceleration*time;


		//moving birds algorithms
		if (even_01.type == ALLEGRO_EVENT_TIMER && shootcount2 >= 0 && draw2==true) {

			//birds vx ve vy coardinats
			if(vy<515){
				vx = vx + (1.3*velocityx*time);
			}

				vy = vy + ((velocityy*time) + 0.5*acceleration*(time*time));
			//vy
			if (vy > 515) {
				vy = 515;
			}

			//for if else,variable
			if (vx<855) {
				draw2 = true;
				if (shootcount == 3) {
					draw2 = false;
					score = 0;
				}
			}

		}

		//boxes's coardinates

		int boxesx = 582, box1y = 358, box2y = 422, box3y = 486;

		//distance between birds and boxes

		float maxboxandball = 57 * (sqrt(2));//this number is max point  between any box and bird
		float box1andball, box2andball, box3andball;

		box1andball = sqrt(pow((vx - boxesx), 2) + pow((vy - box1y), 2));
		box2andball = sqrt(pow((vx - boxesx), 2) + pow((vy - box2y), 2));
		box3andball = sqrt(pow((vx - boxesx), 2) + pow((vy - box3y), 2));

		 //box drawings variable
		if ( box1andball < maxboxandball) {
			box1 = false;

		}

		if ( box2andball < maxboxandball) {
			box1 = false;
			box2 = false;

		}

		if ( box3andball < maxboxandball)
		{
			box1 = false;
			box2 = false;
			box3 = false;

		}

		//drawing algorithms
		if (draw) {
			draw = false;

			  //backround
				al_draw_bitmap(backround1, 0, 0, 0);
				al_draw_bitmap(sling, 200, 200, 0);
				//al_draw_textf(mainfont_40, al_map_rgb(255, 255, 0), 0, 5, 0, "STONE : %d", shootcount);

				switch (shootcount)
				{
				case 1:
					al_draw_bitmap(bird, 5, 5, 0);
					break;
				case 2:
					al_draw_bitmap(bird, 5, 5, 0);
					al_draw_bitmap(bird, 75, 5, 0);
					break;
				case 3:
					al_draw_bitmap(bird, 5,5, 0);
					al_draw_bitmap(bird, 75,5, 0);
					al_draw_bitmap(bird, 145, 5, 0);
					break;
				default:
					break;
				}

				al_draw_text(mainfont_40, al_map_rgb(0, 0, 0), 650, 9, 0, "Angry Birds");
				/*
				//coordinate of mause axes
				al_draw_textf(mainfont_25, al_map_rgb(0, 0, 0), 325, 5, 0, "BALL x : %.f \t\nvx=%.f", x, vx);
				al_draw_textf(mainfont_25, al_map_rgb(0, 0, 0), 325, 30, 0, "BALL y : %.f\t\nvy=%.f", y, vy);
				*/

			if (box1 == false && box2 == false && box3 == false) {

				gameover = true;
				fourclick = 0;
			}

			//boxes drawing	
			if (box1) { 
				al_draw_bitmap(box, 550, 326, 0); 
			}

			if (box2) {
				al_draw_bitmap(box, 550, 390, 0); 
			}

			if (box3) { 
				al_draw_bitmap(box, 550, 454, 0);
			}

			//shot effect
			if (draw2) {
				if (vy == 0) {
					vx = 0;
				}
				al_draw_bitmap(bird, vx-25, vy-25, 0);//kuþ çizimi
				//al_draw_filled_circle(vx, vy, 25, al_map_rgb(255, 0, 255)); //25px çapýnda top çizimi
			}


			if (total<50000) {
				
				al_draw_filled_circle(x, y, 10, al_map_rgb(255, 9, 27));
				al_draw_line(x, y, 240, 210, al_map_rgb(82, 15, 54), 5);
				al_draw_line(x, y, 210, 210, al_map_rgb(82, 15, 54), 5);
			}
			else
			{
				al_draw_filled_circle(150, 250, 10, al_map_rgb(255, 9, 27));
				al_draw_line(150, 260, 240, 210, al_map_rgb(82, 15, 54), 5);
				al_draw_line(150, 260, 210, 210, al_map_rgb(82, 15, 54), 5);

			}

			//for score
			if (fourclick <= 1) {
				al_draw_text(mainfont_30, al_map_rgb(0, 0, 0), 450, 150, 1, "you must click mouse left button for score");
			}

			//gameover WÝN and LOSE
			if (gameover == true) {
				playagain = 0;
				al_draw_bitmap(gamewin, 0, 0, 0);
				al_draw_bitmap(playagainbutton,375,450, 0);
				al_draw_text(mainfont_20, al_map_rgb(0, 0, 0), 325, 550, 0, "Push F5 Button for Playing Again");
				if (starcount == 3) {
						al_draw_bitmap(star, 400, 300, 1);
				}

				 if(starcount == 2) {

					al_draw_bitmap(star, 325, 300, 1);
					al_draw_bitmap(star, 475, 300, 1);
				}

				 if (starcount == 1) {

					al_draw_bitmap(star, 250, 300, 1);
					al_draw_bitmap(star, 400, 300, 1);
					al_draw_bitmap(star, 550, 300, 1);

				}
			}
			else if (gameover == false && shootcount == 0 && fourclick < 1) {
				playagain = 0;
				al_draw_bitmap(gameend, 0, 0, 0);
				al_draw_bitmap(playagainbutton, 375, 450, 0);
				al_draw_text(mainfont_20, al_map_rgb(0, 0, 0), 325,550, 0, "Push F5 Button for Playing Again");
			}
			
			//menu screen
			if (menu) {

				al_draw_bitmap(menuscreen, 0, 0, 0);
				//choosemenu
				if (y < 215 && y>133 && x < 586 && x>285) {
					al_draw_rectangle(285, 133, 586, 215, al_map_rgb(255, 0, 0), 4);
				}
				else if (y < 297 && y>215 && x < 586 && x>227) {

					al_draw_rectangle(285, 215, 586, 297, al_map_rgb(255, 0, 0), 4);
				}

			}
			

			//refresh screen
			al_flip_display();
		}
	}


	//destroy everything
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event);
	al_destroy_sample(soundeffect);
	al_destroy_sample_instance(songinstance);
	return 0;

}
