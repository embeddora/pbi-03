/*
 * Copyright (C) 2018 ARNERI arneri@ukr.net All rights reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Abstract: 
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>


// -----------------------------------------------------------------------------
// ASSERTIONS
// -----------------------------------------------------------------------------
#ifdef _ASSERTIONS_ENABLED //Usually on debug mode only

#define debugBreak() \
    __asm__("int $3") // GCC with Intel only
#define assertFailureMsg(EXP) \
    fprintf(stderr, "[ASSERT] %s:%d: error: ("#EXP") should be true.\n", __FILE__, __LINE__)

// ASSERT Macro
// NOTE: doesn't work like <assert.h>
// If assertion are not enabled, EXP is totally removed
#   define ASSERT(EXP) \
        if (EXP) {} \
        else { \
            assertFailureMsg(EXP); \
            debugBreak(); \
        }
#else
    // Simply skip the insert
#   define ASSERT(EXP)
#endif

#endif // #ifndef _DEBUG_H_
