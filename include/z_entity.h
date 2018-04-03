/*If you didn't notice from the the title of the file
This is to handle entities within the game. Luckily for me
I don't really need much in my entitiy since I'm making pong.
We'll need a sprite, information on position.
*/

#include <SDL.h>
#include <stdlib.h>
#include "gf2d_sprite.h"
#include "z_collision.h"
#include "z_audio.h"
//Define Entity

typedef struct z_entity_S
{
	int entcount;
	Sprite * z_entSprite;
	Uint16 score;
	Vector2D position;
	Uint8 inuse;
	char* name;
	Sound* audios;
	SDL_Rect collider;
	void(*draw)(struct z_entity_S *self);
	void(*think)(struct z_entity_S *self);
	void(*die)(struct z_entity_S *self);
	int xvel;
	int yvel;

}z_entity;
//init entity manager
void z_entity_init(Uint32 max);
//returns address of ent
z_entity *z_entity_new();
//Don't know yet.
Vector2D z_entity_position(z_entity pos);
//It draws things
void z_entity_draw();
//Kills ent =[
void  z_entity_die(z_entity *self);

Uint8 z_collision_test(SDL_Rect a, SDL_Rect b);
//Ball's think funtion. =]
void z_ball_move(z_entity* self);

void z_collision_ball(z_entity *ball, z_entity* paddle, z_entity *paddle2, z_entity *top, z_entity *bottom, z_entity *left, z_entity *right, int *y, int *y2,int *x, int* x2);