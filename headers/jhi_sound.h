//****************************************************************************
//*  This file contains functions structure of the Music and Effect.		 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef SOUND_H
#define SOUND_H
/**
 *  \file		jhi_sound.h
 *  \brief	   	This file contains functions and structures of the Music and Effect.
 */
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>

/**
 * \brief Struct of configuration of the Music
 */
typedef struct {
	Mix_Music *mix_music; /**< SDL structure of Music.*/
}JHI_Music;

/**
 * \brief Struct of the configuration of the Effect
 */
typedef struct {
	Mix_Chunk *mix_chunk; /**< SDL structure of Effect.*/
}JHI_Effect;

/**
 * \brief Load the music with the filename
 * \param music				Structure of music to load
 * \param filename			Name of music file
 */
void jhi_load_music(JHI_Music *music, const char *filename);

/**
 * \brief Play the music in the background
 * \param music				Structure of music to load
 * \param loop				Number of times that music will played. -1, it's infinite
 */
void jhi_play_music(JHI_Music *music, int loop);

/**
 * \brief Stop the current music
 */
void jhi_stop_music();

/**
 * \brief Pause the current music
 */
void jhi_pause_music();

/**
 * \brief Free music structure
 */
void jhi_free_music(JHI_Music *music);

/**
 * \brief Load the effect with the filename
 * \param effect			Structure of effect to load
 * \param filename			Name of the effect file
 */
void jhi_load_effect(JHI_Effect *effect, const char *filename);

/**
 * \brief Play the effect
 * \param effect			Structure of effect to play
 * \param delay				Delay to play the effect in Seconds
 */
void jhi_play_effect(JHI_Effect *effect, int delay);

/**
 * \brief Free effect structure
 */
void jhi_free_effect(JHI_Effect *effect);

#endif
