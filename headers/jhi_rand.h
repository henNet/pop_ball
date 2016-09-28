#ifndef JHI_RAND_H
#define JHI_RAND_H

#include <stdlib.h>


/**
 *  \file		jhi_rand.h
 *  \brief	   	This file contains rand auxiliary MACROS.
 *
 */

/**
 * \brief get a rand value between a,b
 */
#define RAND_INTERVAL(a, b) (rand() % ((b)-(a+1))) + (a)
/**
 * \brief get a double rand value between 0,1
 */
#define RAND_01 ((double)(rand())/(double)(RAND_MAX))

#endif
