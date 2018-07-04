#include <iostream>  

#include <allegro.h> 
#include <math.h> 
#define DEGREES(x) int((x)/360.0*0xFFFFFF) 

using namespace std;
BITMAP *buffer;
float x = 100.0;
float y = 100.0;
float velocity = 50;

float theta = DEGREES(45); // degree at which to throw the ball.  
float velocityX = velocity * cos(theta); // x component of velocity 
float velocityY = velocity * sin(theta); // y component of velocity 
float acc = 9.8; // acceleration  
float dt = 0.1; // change in time. 

int main(int argc, char *argv[]) {

	allegro_init();    // init Allegro 
	install_keyboard();  // setup allegro keyboard 

	set_color_depth(16);
	if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,
		640, 480, 0, 0)<0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Failure to init video mode!\n%s\n",
			allegro_error);
	}

	buffer = create_bitmap(640, 480); // creating the buffer; 

	while ((!key[KEY_ESC]) && (!key[KEY_SPACE])) {
		// Notice there is no update for the x component of velocity. this is because it is constant. 
		velocityY = velocityY + acc*dt; // updating the y component of the velocity  
		x = x + (velocityX*dt); // updating the x position  
		y = y + (velocityY*dt) + 0.5*acc*(dt*dt);// updating the y position. 
		rest(5);

		circlefill(buffer, x, y, 4, makecol(200, 0, 0));// creating the circle on the buffer.  

		draw_sprite(screen, buffer, 0, 0); // drawing the buffer to the screen.  

										   //clear_bitmap(buffer); 

	}

	cout << "Hello world!" << endl;
	return 0;
}
END_OF_MAIN();