#include "z_audio.h"
#include "simple_logger.h"
#include <stdio.h>
typedef struct {
	Uint32 max_tracks;
	Sound *soundlist;
}audomanager;
char* filename;
static audomanager audio_manager;
FILE *fp;
long duration;
void z_audio_init(Uint32 max) {
	if (!max) {
		slog("Failed to initialize audio manager");
		return;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		slog("Error opening audio device %s", Mix_GetError());
		return;
	}
	Mix_AllocateChannels(max);
	audio_manager.max_tracks = max;
	audio_manager.soundlist = (Sound*)malloc(sizeof(Sound)*max);
	memset(audio_manager.soundlist, 0, sizeof(Sound)*max);
	slog("Successfully created audio manager");
}

Sound *z_audio_new(char* filepath) {
	for (int i = 0; i < audio_manager.max_tracks; i++) {
		if (audio_manager.soundlist[i].inuse == 0) {
			slog("%s", filepath);
			audio_manager.soundlist[i].inuse = 1;
			audio_manager.soundlist[i].a_chunk = Mix_LoadWAV(filepath);
			slog("Error: %s\n", Mix_GetError());
			audio_manager.soundlist[i].channel = i;
			audio_manager.soundlist[i].filepath = filepath;
			audio_manager.soundlist[i].play = z_audio_play;
			audio_manager.soundlist[i].pause = z_audio_pause;
			audio_manager.soundlist[i].resume = z_audio_resume;
			audio_manager.soundlist[i].stop = z_audio_stop;
			audio_manager.soundlist[i].stutter = z_audio_stutter;
			audio_manager.soundlist[i].duration = z_audio_duration;
			return &audio_manager.soundlist[i];
			if (!audio_manager.soundlist[i].a_chunk) {
				slog("Error: %s\n",Mix_GetError() );
			}
			else {
				slog("Audio loaded", filepath);
				slog(filepath);
			}
		}
		//return &audio_manager.soundlist[i];
	}

}

void z_audio_play(Sound *self) {
	if (!self->a_chunk) {
		slog("Audio was null. wtf?");
		return;
	}
	Mix_PlayChannel(self->channel, self->a_chunk, 0);
	slog(self->filepath, Mix_GetError());
	slog("%d",self->channel);
	return;
}
void z_audio_pause(Sound *self) {
	Mix_Pause(self->channel);
}

void z_audio_stop(Sound *self) {
	Mix_HaltChannel(self->channel);
}

void z_audio_resume(Sound *self) {
	Mix_Resume(self->channel);
}

void z_audio_stutter(Sound *self) {
	z_audio_pause(self);
	z_audio_resume(self);
}

//SDL_MIXER DOESNT HAVE THIS. WHAT THE ACTUAL FUCK!?
void z_audio_duration(Sound *self) {
	fp = fopen(self->filepath,"rb");
	if (fp == NULL) {
		slog("You're bad at opening files");
		return;
	}
	fseek(fp, 0, SEEK_END);
	//slog(ftell(fp));
	duration = ftell(fp);
	duration = duration / (176400);
	printf("%d", duration);
	slog("Duration of file in secs is: %d",duration);
	return;
	//self->a_chunk->alen/()
}


