/*
 * Copyright (c) 1999-2000 Image Power, Inc. and the University of
 *   British Columbia.
 * Copyright (c) 2001-2002 Michael David Adams.
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
 * MQ Arithmetic Encoder
 *
 * $Id$
 */

#ifndef JPC_MQENC_H
#define JPC_MQENC_H

/******************************************************************************\
* Includes.
\******************************************************************************/

#include "jas_types.h"
#include "jas_stream.h"

#include "jpc_mqcod.h"

#include <stdio.h>

/******************************************************************************\
* Constants.
\******************************************************************************/

/*
 * Termination modes.
 */

#define	JPC_MQENC_DEFTERM	0	/* default termination */
#define	JPC_MQENC_PTERM		1	/* predictable termination */

/******************************************************************************\
* Types.
\******************************************************************************/

/* MQ arithmetic encoder class. */

typedef struct {

	/* The C register. */
	uint_least32_t creg;

	/* The A register. */
	uint_least32_t areg;

	/* The CT register. */
	uint_least32_t ctreg;

	/* The maximum number of contexts. */
	unsigned maxctxs;

	/* The per-context information. */
	const jpc_mqstate_t **ctxs;

	/* The current context. */
	const jpc_mqstate_t **curctx;

	/* The stream for encoder output. */
	jas_stream_t *out;

	/* The byte buffer (i.e., the B variable in the standard). */
	int_least16_t outbuf;

	/* The last byte output. */
	int_least16_t lastbyte;

	/* The error indicator. */
	bool err;
	
} jpc_mqenc_t;

/* MQ arithmetic encoder state information. */

typedef struct {

	/* The A register. */
	unsigned areg;

	/* The C register. */
	unsigned creg;

	/* The CT register. */
	unsigned ctreg;

	/* The last byte output by the encoder. */
	int lastbyte;

} jpc_mqencstate_t;

/******************************************************************************\
* Functions/macros for construction and destruction.
\******************************************************************************/

/* Create a MQ encoder. */
jpc_mqenc_t *jpc_mqenc_create(unsigned maxctxs, jas_stream_t *out);

/* Destroy a MQ encoder. */
void jpc_mqenc_destroy(jpc_mqenc_t *enc);

/******************************************************************************\
* Functions/macros for initialization.
\******************************************************************************/

/* Initialize a MQ encoder. */
void jpc_mqenc_init(jpc_mqenc_t *enc);

/******************************************************************************\
* Functions/macros for context manipulation.
\******************************************************************************/

/* Set the current context. */
static inline void jpc_mqenc_setcurctx(jpc_mqenc_t *enc, unsigned ctxno) {
	enc->curctx = &enc->ctxs[ctxno];
}

/* Set the state information for multiple contexts. */
void jpc_mqenc_setctxs(jpc_mqenc_t *enc, unsigned numctxs, const jpc_mqctx_t *ctxs);

/******************************************************************************\
* Miscellaneous functions/macros.
\******************************************************************************/

/* Get the error state of a MQ encoder. */
static inline bool jpc_mqenc_error(const jpc_mqenc_t *enc) {
	return enc->err;
}

/* Get the current encoder state. */
void jpc_mqenc_getstate(const jpc_mqenc_t *enc, jpc_mqencstate_t *state);

/* Terminate the code. */
int jpc_mqenc_flush(jpc_mqenc_t *enc, int termmode);

/******************************************************************************\
* Functions/macros for encoding bits.
\******************************************************************************/

/******************************************************************************\
* Functions/macros for debugging.
\******************************************************************************/

int jpc_mqenc_dump(const jpc_mqenc_t *mqenc);

/******************************************************************************\
* Implementation-specific details.
\******************************************************************************/

/* Note: These function prototypes are included only to satisfy the
  needs of the mqenc_putbit_macro macro.  Do not call any of these
  functions directly. */
int jpc_mqenc_codemps2(jpc_mqenc_t *enc);
int jpc_mqenc_codelps(jpc_mqenc_t *enc);

int jpc_mqenc_putbit(jpc_mqenc_t *enc, bool bit);

#endif
