#ifndef _CHOBITS_API_H_
#define _CHOBITS_API_H_

/*
 * INCLUDE FILES
 */
#include "../types.h"

#include "../syscall_type.h"


/*
 * API CALLs
 */

/* system api */
VOID API_ExitProgram(VOID);

/* screen associated */
VOID API_PrintText(BYTE *pText);


#endif /* #ifndef _CHOBITS_API_H_ */