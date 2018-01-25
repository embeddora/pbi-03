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
// INLINE.
// General inlined definitions for Vector. (Common for SSE, FPU etc).
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF3 const& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

FORCE_INLINE float VectF3::operator[](const size_t index) const {
    return (&x)[index];
}

FORCE_INLINE float& VectF3::operator[](const size_t index){
    return *(&x+index);
}


// -----------------------------------------------------------------------------
// Add implementation specific to an optimization
// -----------------------------------------------------------------------------
#ifdef __SSE4_1__
#   include "VectF3_SSE.inl"
#else
#   include "VectF3_FPU.inl"
#endif
