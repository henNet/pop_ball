//****************************************************************************
//*  This file contains functions structure of the Timer, to control		 *
//*	 number of frames per second (fps).	 									 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHITIMER_H
#define JHITIMER_H
/**
 *  \file		jhi_timer.h
 *  \brief	   	This file contains functions structure of the Timer to control number of frames per second (fps).
 */
#include "SDL/SDL.h"

/**
 * \brief Configure the fps timer
 * \param fps	Frames per second to animation
 */
void jhi_set_fps_timer(int fps);

int jhi_get_fps_timer();

/**
 * \brief Start the count to fps
 */
void jhi_timer_start();

/**
 * \brief Wait the time necessary to control fps
 */
void jhi_wait_time();

/**
 * \brief Wait the time in second
 * \param second Number of Seconds to wait
 */
void jhi_delay_seconds(int seconds);

void jhi_delay_mili_seconds(int ms);

#endif
