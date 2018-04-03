#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_vector.h"
#include "z_entity.h"
#include "defparser.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *background;
	Sprite *paddle_img;
	Sprite *ball_img;
	Sprite *crowd_img;
	Sprite *crowd_img2;
	z_entity *paddle;
	z_entity *paddle2;
	z_entity *ball;
	z_entity *top;
	z_entity *bottom;
	z_entity *left;
	z_entity *right;
	z_entity *crowd[9];
	z_entity *crowd2[9];
	Sound *BGM;
	Sound *BGM2;
	Vector4D *colortest;
	char* song;
	char* paddlepath;
	char* ballpath;
	int pauseflag = 0;
    int mx,my,i;
	i = 0;
    float mf = 0;
	int x = 0;
	int y = 250;
	int x2 = 1150;
	int y2 = 250;
	int *yy = &y;
	int *yy2 = &y2;
	int *xx = &x;
	int *xx2 = &x2;
    Sprite *mouse;
	z_entity *meeps;
    Vector4D mouseColor = {255,138,23,200};

    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(8);
	z_entity_init(27);
	z_audio_init(2048);
	//datainit(16);
    SDL_ShowCursor(SDL_DISABLE);
	z_file_load();
	paddlepath = getpaddle();
	song = getsong();
	ballpath = getball();
	slog("%s", song);
    /*demo setup
	Need to make this more compact at a later time. This is disgusting.
	*/
	//Setup background and ents
    background = gf2d_sprite_load_image("images/backgrounds/background.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	crowd_img = gf2d_sprite_load_image("images/crowd1.png");
	crowd_img2 = gf2d_sprite_load_image("images/crowd2.png");
	ball_img = gf2d_sprite_load_image(strtok(ballpath,"\n"));
	paddle_img = gf2d_sprite_load_image(strtok(paddlepath,"\n"));
	//Ents
	for (int i = 0; i <= 9; i++) {
		crowd[i] = z_entity_new();
		crowd2[i] = z_entity_new();
		crowd[i]->z_entSprite = crowd_img;
		crowd2[i]->z_entSprite = crowd_img2;
		crowd[i]->position.x += 72 * i;
		crowd[i]->position.y = 648;
		crowd2[i]->position.x = 1200 - 72 * i;
		crowd[i]->inuse = 1;
		crowd2[i]->inuse = 1;
	}
	paddle2 = z_entity_new();
	paddle = z_entity_new();
	ball = z_entity_new();
	top = z_entity_new();
	bottom = z_entity_new();
	left = z_entity_new();
	right = z_entity_new();
	//load sptires/audio/collider boxes
	paddle2->z_entSprite = paddle_img;
	paddle->z_entSprite = paddle_img;
	ball->z_entSprite = ball_img;
	ball->position.x = 600;
	ball->position.y = 360;
	//Colliders
	paddle->collider.h = 175;
	paddle->collider.w = 100;
	paddle2->collider.h = 175;
	paddle2->collider.w = 50;
	ball->collider.h = 72;
	ball->collider.w = 72;
	ball->think = z_ball_move;

	//Border

	top->collider.h = 1;
	top->collider.w = 2560;
	top->collider.x = 0;
	top->collider.y = 720;

	bottom->collider.h = 1;
	bottom->collider.w = 2560;
	bottom->collider.x = 0;
	bottom->collider.y = 0;

	right->collider.h = 99999;
	right->collider.w = 100;
	right->collider.x = 1200;
	right->collider.y = 0;

	left->collider.h = 2560;
	left->collider.w = 50;
	left->collider.x = 0;
	left->collider.y = 0;

	
	//Audio
	paddle2->audios = z_audio_new("sound/rhit.wav");
	paddle->audios = z_audio_new("sound/lhit.wav");
	//BGM = z_audio_new("olko.wav");
	BGM2 = z_audio_new(strtok(song,"\n"));
	//(BGM->play)(BGM);
	(BGM2->play)(BGM2);
	(BGM2->duration)(BGM2);
	//define velocity
	ball->xvel = 3;
	//ball->yvel = -3;

	paddle->name = "Ayyy";

    /*main game loop*/
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);
		Vector4D nmouseColor= { mx, my, 0, 200 };		
        mf+=0.1;
        if (mf >= 16.0)mf = 0;

        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(background,vector2d(0,0));
			paddle->position = vector2d(x, y);
			paddle2->position = vector2d(x2, y2);
			z_entity_draw_all();
            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &nmouseColor,
                (int)mf);

		//Collosion check
		z_collision_ball(ball,paddle, paddle2,top,bottom,left,right,yy,yy2,xx,xx2);
		(*ball->think)(ball);

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        //Control Conditions

		//p2 movement
		if (keys[SDL_SCANCODE_UP])y2-=5;
		if (keys[SDL_SCANCODE_DOWN])y2 += 5;
		//p1 movement
		if (keys[SDL_SCANCODE_W])y -= 5; 
		if (keys[SDL_SCANCODE_S])y += 5;
		//paddle swing (this should be a function but eh, we made a mess already of this)
		if (keys[SDL_SCANCODE_SPACE]) {
			if (paddle->position.x > 300) {
				x = 300;
			}
			else {
				x += 10;
			}
		}
		else {
			x = 0;
		}
		//paddle 2 swing
		if (keys[SDL_SCANCODE_RETURN]) {
			if (paddle2->position.x < 900) {
				x2 = 900;
			}
			else {
				x2 -= 10;
			}
		}
		else {
			x2 = 1150;
		}

		if (keys[SDL_SCANCODE_0] && i > 60) { 
			(*paddle->die)(paddle); 
			i = 0; 
		}
		if (paddle->score < 10) {
			//crowd[paddle2->score]->inuse = 0;
			crowd2[paddle->score]->inuse = 0;
		}
		if (paddle2->score < 10) {
			//crowd[paddle2->score]->inuse = 0;
			crowd[paddle2->score]->inuse = 0;
		}
		
		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
		i++;
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
