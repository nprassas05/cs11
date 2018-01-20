/*
	optionally can use explicit checking of pre and post
	conditions with name-friendly aliases for the 
	assert statement.

	This makefile was taken and adapted from Frank Pfenning
	of CMU.
 */

#include <cassert>

/* The comment below was written by Frank Pfenning. It is kept
   here because it is useful */

/* Unlike typical header files, "contracts.h" may be
 * included multiple times, with and without DEBUG defined.
 * For this to succeed we first undefine the macros in
 * question in order to avoid a redefinition warning.
 */

#undef ASSERT
#undef PRE_COND
#undef INVARIANT
#undef POST_COND

#ifdef DEBUG

#define ASSERT(COND) assert(COND)
#define PRE_COND(COND) assert(COND)
#define POST_COND(COND) assert(COND)
#define INVARIANT(COND) assert(COND)

#else

#define PRE_COND(COND) ((void)0)
#define POST_COND(COND) ((void)0)
#define ASSERT(COND) ((void)0)
#define INVARIANT(COND) ((void) 0)

#endif
