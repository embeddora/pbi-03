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

#ifndef _CONFIG_H_
#define _CONFIG_H_

// FORCE_INLINE MACRO
#ifdef _DEBUG
#   define FORCE_INLINE inline // In Debug mode, doesn't fore inline
#else
#   define FORCE_INLINE inline __attribute__((always_inline))
#endif


#define GCC_ALIGNED(n) __attribute__((aligned(n)))


#endif // #ifndef _CONFIG_H_
