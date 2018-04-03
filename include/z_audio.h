/*If you didn't notice from the the title of the file
This is to handle entities within the game. Luckily for me
I don't really need much in my entitiy since I'm making pong.
We'll need a sprite, information on position.
*//*Where the audio magic happens =]*/
#include <SDL.h>
#include <stdlib.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>
#include "gf2d_types.h"
#include "gf2d_text.h"


typedef struct Sound_S{
	char* filepath;
	Mix_Chunk *a_chunk;
	Uint8 inuse;
	float volume;
	int channel;
	void(*play)(struct Sound_S *self);
	void(*pause)(struct Sound_S *self);
	void(*resume)(struct Sound_S *self);
	void(*stop)(struct Sound_S *self);
	void(*stutter)(struct Sound_S *self);
	void(*duration)(struct Sound_S *self);
}Sound;


//Creates Audio manager.
void z_audio_init(Uint32 max);
//Returns audio sample
Sound *z_audio_new(char* filepath);
//Pointer function for playing Sound ent.
void z_audio_play(Sound *self);
// =[
void z_audio_resume(Sound *self);

void z_audio_stop(Sound *self);

void z_audio_pause(Sound *self);
//This one needs some work.
void z_audio_stutter(Sound *self);

//getting song duration
//Only works for 16bit, 2 channel wav files.
//Lesser audio doesnt matter. =]
void z_audio_duration(Sound *self);