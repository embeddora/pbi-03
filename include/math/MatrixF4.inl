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

// =============================================================================
// INLINE
// Contains matrix function common to all kind of optimization (SSE, FPU etc)
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Special class members
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4 MatrixF4::IDENTITY() {
    return MatrixF4(
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1);
}

FORCE_INLINE MatrixF4 MatrixF4::ZERO() {
    return MatrixF4(
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0);
}


// -----------------------------------------------------------------------------
// Add function specific to optimization type
// -----------------------------------------------------------------------------
#ifdef __SSE4_1__
#   include "MatrixF4_FPU.inl" //TODO Tmp: For now, only FPU exists
#else
#   include "MatrixF4_FPU.inl"
#endif
