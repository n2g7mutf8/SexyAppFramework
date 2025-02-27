/*
 * Copyright (c) 2004 Michael David Adams.
 * All rights reserved.
 */

/* __START_OF_JASPER_LICENSE__
 * 
 * JasPer License Version 2.0
 * 
 * Copyright (c) 2001-2006 Michael David Adams
 * Copyright (c) 1999-2000 Image Power, Inc.
 * Copyright (c) 1999-2000 The University of British Columbia
 * 
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person (the
 * "User") obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 * 
 * 1.  The above copyright notices and this permission notice (which
 * includes the disclaimer below) shall be included in all copies or
 * substantial portions of the Software.
 * 
 * 2.  The name of a copyright holder shall not be used to endorse or
 * promote products derived from the Software without specific prior
 * written permission.
 * 
 * THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS
 * LICENSE.  NO USE OF THE SOFTWARE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.  THE SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  NO ASSURANCES ARE
 * PROVIDED BY THE COPYRIGHT HOLDERS THAT THE SOFTWARE DOES NOT INFRINGE
 * THE PATENT OR OTHER INTELLECTUAL PROPERTY RIGHTS OF ANY OTHER ENTITY.
 * EACH COPYRIGHT HOLDER DISCLAIMS ANY LIABILITY TO THE USER FOR CLAIMS
 * BROUGHT BY ANY OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL
 * PROPERTY RIGHTS OR OTHERWISE.  AS A CONDITION TO EXERCISING THE RIGHTS
 * GRANTED HEREUNDER, EACH USER HEREBY ASSUMES SOLE RESPONSIBILITY TO SECURE
 * ANY OTHER INTELLECTUAL PROPERTY RIGHTS NEEDED, IF ANY.  THE SOFTWARE
 * IS NOT FAULT-TOLERANT AND IS NOT INTENDED FOR USE IN MISSION-CRITICAL
 * SYSTEMS, SUCH AS THOSE USED IN THE OPERATION OF NUCLEAR FACILITIES,
 * AIRCRAFT NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL
 * SYSTEMS, DIRECT LIFE SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH
 * THE FAILURE OF THE SOFTWARE OR SYSTEM COULD LEAD DIRECTLY TO DEATH,
 * PERSONAL INJURY, OR SEVERE PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH
 * RISK ACTIVITIES").  THE COPYRIGHT HOLDERS SPECIFICALLY DISCLAIM ANY
 * EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR HIGH RISK ACTIVITIES.
 * 
 * __END_OF_JASPER_LICENSE__
 */

/*
 * Timing Routines
 *
 * $Id$
 */

/******************************************************************************\
* Includes.
\******************************************************************************/

#define JAS_FOR_INTERNAL_USE_ONLY

#include "jas_tmr.h"

#include <stdlib.h>

/******************************************************************************\
* Code.
\******************************************************************************/

#if defined(JAS_HAVE_GETTIMEOFDAY)

void jas_tmr_start(jas_tmr_t *tmr)
{
	if (gettimeofday(&tmr->start, 0)) {
		abort();
	}
}

void jas_tmr_stop(jas_tmr_t *tmr)
{
	if (gettimeofday(&tmr->stop, 0)) {
		abort();
	}
}

double jas_tmr_get(jas_tmr_t *tmr)
{
	double t0;
	double t1;
	t0 = ((double) tmr->start.tv_sec) + ((double) tmr->start.tv_usec) / 1e6;
	t1 = ((double) tmr->stop.tv_sec) + ((double) tmr->stop.tv_usec) / 1e6;
	return t1 - t0;
}

#elif defined(JAS_HAVE_GETRUSAGE)

void jas_tmr_start(jas_tmr_t *tmr)
{
	if (getrusage(RUSAGE_SELF, &tmr->start) < 0) {
		abort();
	}
}

void jas_tmr_stop(jas_tmr_t *tmr)
{
	if (getrusage(RUSAGE_SELF, &tmr->stop) < 0) {
		abort();
	}
}

double jas_tmr_get(jas_tmr_t *tmr)
{
	double t;
	t = ((tmr->stop.ru_utime.tv_sec * 1e6 + tmr->stop.ru_utime.tv_usec) -
	  (tmr->start.ru_utime.tv_sec * 1e6 + tmr->start.ru_utime.tv_usec)) / 1e6;
	t += ((tmr->stop.ru_stime.tv_sec * 1e6 + tmr->stop.ru_stime.tv_usec) -
	  (tmr->start.ru_stime.tv_sec * 1e6 + tmr->start.ru_stime.tv_usec)) / 1e6;
	return t;
}

#else

void jas_tmr_start(jas_tmr_t *tmr)
{
}

void jas_tmr_stop(jas_tmr_t *tmr)
{
}

double jas_tmr_get(jas_tmr_t *tmr)
{
	return 0.0;
}

#endif
