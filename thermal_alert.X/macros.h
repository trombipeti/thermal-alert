#ifndef MACROS_H
#define	MACROS_H

#define CALLBACK(f) if(f != NULL) { f(); }
#define CALLBACK_PARAM(f, p) if(f != NULL) { f(p); }

#ifndef isdigit
#define isdigit(c)  ((c) >= '0' && (c) <= '9')
#endif

#ifndef isalpha
#define isalpha(c)  ( ((c) >= 'A' && (c) <= 'Z') || ( (c) >= 'a' && (c) <= 'z' ) )
#endif

#ifndef isalnum
#define isalnum(c)  (isalpha(c) || isdigit(c))
#endif

#endif	/* MACROS_H */

