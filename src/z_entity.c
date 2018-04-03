#include <stdlib.h>
#include <SDL.h>
#include "gf2d_sprite.h"
#include "z_entity.h"
#include "simple_logger.h"

z_entity test;
typedef struct 
{
	Uint32 max_entities;
	z_entity * entity_list;
}EntityManager;
static EntityManager entity_manager;
static z_entity zent;
void z_entity_init(Uint32 max)
{
	if (!max) {
		slog("Failed to initialize entities");
		return;
	}
	entity_manager.max_entities=max;
	entity_manager.entity_list = (z_entity*)malloc(sizeof(z_entity)*max);
	memset(entity_manager.entity_list, 0, sizeof(z_entity)*max);
	slog("Successfully created entity manager",&entity_manager.max_entities);


}
void z_entity_clear() {
	
	free(entity_manager.entity_list,0,sizeof(z_entity));
}

void z_entity_close() {
	z_entity_clear();
	slog("Ents closed.");
}

z_entity *z_entity_new() {
	for (int i = 0;i < entity_manager.max_entities; i++) {
		if (entity_manager.entity_list[i].inuse==0)
		{
			entity_manager.entity_list[i].inuse = 1;
			entity_manager.entity_list[i].draw = z_entity_draw;
			entity_manager.entity_list[i].die = z_entity_die;
			//slog("Entity created");
			return &entity_manager.entity_list[i];	
		}

	}
	slog("Max amount of entities has been reached.");
	/*zent.z_entSprite = sprite;
	zent.position = position;
	zent.score = score;*/
	return NULL;
}
Vector2D z_entity_position(z_entity pos) {
	return;
}

void z_entity_draw(z_entity *self) {
	if (self->inuse == 1) {
		if (self->z_entSprite->frames_per_line > 1)
		{

			gf2d_sprite_draw(
				self->z_entSprite,
				self->position,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL
			);
		}
		else
		{
			gf2d_sprite_draw_image(self->z_entSprite, self->position);
		}
		self->collider.x = self->position.x;
		self->collider.y = self->position.y;

	}

}
void z_entity_draw_all() 
	{
		for (int i = 0; i < entity_manager.max_entities; i++) {
			if (entity_manager.entity_list[i].inuse == 1 && entity_manager.entity_list[i].z_entSprite!=NULL) {
				z_entity_draw(&entity_manager.entity_list[i]);
			}
		}
	}

void  z_entity_die(z_entity *self) {
	if (self->inuse == 1) {
		self->inuse = 0;
		slog("Oh my god you killed!: %s", self->name );
		slog(" You bastards!");
		memset(self, 0, sizeof(z_entity));
	}
}

void z_ball_collision(z_entity *self) {


}
Uint8 z_collision_test(SDL_Rect a, SDL_Rect b) {
	if (checkCollision(a, b)==1) {
		return 1;
	}
	else {

		return NULL;
	}
}
//This really shouldnt be here....but oh well? I might as well call this super think. 
//I'm abusing things really hard here.
void z_collision_ball(z_entity *ball, z_entity* paddle, z_entity *paddle2,z_entity *top, z_entity *bottom, z_entity *left, z_entity *right,int *y,int *y2,int *x, int* x2) {
	if (z_collision_test(ball->collider, paddle->collider) == 1) {
		//slog("you hit the ball");
		ball->xvel = 10;
		ball->yvel = 1;
		*x = 0;
		(paddle->audios->play)(paddle->audios);
	}
	if (z_collision_test(ball->collider, paddle2->collider) == 1) {
		//slog("you hit the ball");
		ball->xvel = -10;
		ball->yvel = -1;
		(paddle2->audios->play)(paddle2->audios);
		*x2 = 1150;
	}
	if (z_collision_test(ball->collider, top->collider) == 1) {
		//slog("you hit top");
		ball->yvel = -1;
	}
	if (z_collision_test(ball->collider, bottom->collider) == 1) {
		//slog("you hit bottom");
		ball->yvel = 1;
	}
	if (z_collision_test(ball->collider, left->collider) == 1) {
		//slog("you hit left");
		ball->xvel = 10;
		paddle2->score += 1;
		//slog("Player 2: %d", paddle2->score);
	}	if (z_collision_test(ball->collider, right->collider) == 1) {
		//slog("you hit right");
		ball->xvel = -10;
		paddle->score += 1;
		//slog("Player 1: %d", paddle->score);
	}
	if (z_collision_test(paddle->collider, top->collider) == 1) {
		*y = 545;
	}
	if (z_collision_test(paddle->collider, bottom->collider) == 1) {
		*y = 0;
	}
	if (z_collision_test(paddle2->collider, top->collider) == 1) {
		*y2 = 545;
	}
	if (z_collision_test(paddle2->collider, bottom->collider) == 1) {
		*y2 = 0;
	}
}

void z_ball_move(z_entity* self) {
	self->position.x += self->xvel;
	self->position.y += self->yvel;
}

void z_think_all() {
	for (int i = 0; i < entity_manager.max_entities; i++) {
		if (entity_manager.entity_list[i].inuse == 1) {
			//(entity_manager.entity_list[i]->think
		}
	}
}

z_entity *crowdload(Uint32 max) {
	//z_entity* tempreturn[max];
	for (int i = 0; i < max; i++) {

	}

}

//z_entity *z_entity_launch