#include "jhi_sound.h"

void jhi_load_music(JHI_Music *music, const char *filename)
{
	//Load the music
	music->mix_music = NULL;
	music->mix_music = Mix_LoadMUS(filename);

	//If there was a problem loading the music
	if(music->mix_music == NULL)
	{
		printf("File %s not found.\n", filename);
	}
}

void jhi_play_music(JHI_Music *music, int loop)
{

	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}

	else if(Mix_PlayingMusic() == 0) {
		if(Mix_PlayMusic(music->mix_music, loop) == -1 )
		{
			printf("Error while playing music.\n");
		}
	}
}

void jhi_stop_music()
{
	Mix_HaltMusic();
}

void jhi_pause_music()
{
	Mix_PauseMusic();
}

void jhi_free_music(JHI_Music *music)
{
	Mix_FreeMusic(music->mix_music);
}

void jhi_load_effect(JHI_Effect *effect, const char *filename)
{
	effect->mix_chunk = NULL;
	effect->mix_chunk = Mix_LoadWAV(filename);

	if(effect->mix_chunk == NULL)
	{
		printf("File %s not found.\n", filename);
		exit(1);
	}
}

void jhi_play_effect(JHI_Effect *effect, int delay)
{

	if( Mix_PlayChannel( -1, effect->mix_chunk, 0 ) == -1 )
	{
		printf("Error while playing effect.\n");
	}

	SDL_Delay(delay);
}

void jhi_free_effect(JHI_Effect *effect)
{
	Mix_FreeChunk(effect->mix_chunk);
}
