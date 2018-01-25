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

#ifndef _VECTF3_H_
#define _VECTF3_H_

#include <iostream>
#include <cmath>
#ifdef __SSE4_1__
#   include <x86intrin.h>
#endif

#include "core/config.h"


/**
 * 3 Dimensions vector with floating point precision.
 *
 * \since   Jun 4, 2017
 * \author  Constantin MASSON
 */
class VectF3 {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    public:
        union{
            struct{
                float x;
                float y;
                float z;
            };
            struct {
                // Useful for colors (Red / Green / Blue)
                float r;
                float g;
                float b;
            };
#ifdef __SSE4_1__
            __m128 m128; // Last element is not used
#endif
        };

    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        /**
         * Create a new null vector (All components to 0).
         */
        VectF3();

        /**
         * Create initialized vector.
         *
         * \param x The x value to set.
         * \param y The y value to set.
         * \param z The z value to set.
         */
        explicit VectF3(const float x, const float y, const float z);

        /**
         * Create initialized vector.
         * Each components are set with the given value.
         *
         * \param s Value to set for all components.
         */
        explicit VectF3(const float s);

#ifdef __SSE4_1__
        explicit VectF3(const __m128 v);
#endif


    // -------------------------------------------------------------------------
    // Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Gets the length of this vector.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length() const;

        /**
         * Gets the square length of this vector.
         *
         * \return The square length (Magnitude) of this vector.
         */
        float squareLength() const;

        /**
         * Returns a normalized copy of this vector.
         *
         * \warning
         * If vector length is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * \return The new normalized vector.
         */
        VectF3 getNormalFast() const;

        /**
         * Normalize this vector in place.
         *
         * \warning
         * If vector length is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         */
        void normalizeFast();

        /**
         * Gets Cross Product of this vector with another.
         * (a.k.a vector product or outer product).
         *
         * \param v Vector to cross with.
         * \return The Vector cross product (this x other).
         */
        VectF3 getCrossProduct(VectF3 const& v) const;


    // -------------------------------------------------------------------------
    // Static Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Gets the Dot Product of 2 vectors.
         * (a.k.a scalar product or inner product).
         *
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return The dot product (v1.v2).
         */
        static float dotProduct(VectF3 const& v1, VectF3 const& v2);

        /**
         * Gets the Cross Product of 2 vectors.
         * (a.k.a vector product or outer product).
         *
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return The Vector cross product (v1 x v2).
         */
        static VectF3 crossProduct(VectF3 const& v1, VectF3 const& v2);


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:
        /**
         * Sets all axis values of this.
         *
         * \param x New x coordinate.
         * \param y New y coordinate.
         * \param z New z coordinate.
         */
        void set(float const x, float const y, float const z);

        /**
         * Copy values of the given vector in this.
         *
         * \param v Vector to use as copy.
         */
        void set(VectF3 const& v);

#ifdef __SSE4_1__
        void set(const __m128 v);
#endif


    // -------------------------------------------------------------------------
    // Operators overload
    // -------------------------------------------------------------------------
    public:

        /**
         * Returns the multiplication of each this components by a scalar.
         *
         * \param s Scalar to apply.
         * \return The new Vector.
         */
        VectF3 operator*(float const s) const;

        /**
         * Returns the multiplication of this by another vector.
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF3 operator*(VectF3 const& v) const;

        /**
         * Returns the division of each this components by a scalar.
         *
         * \warning
         * If scalar is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * \param v Vector to divide with.
         * \return New vector.
         */
        VectF3 operator/(float const s) const;

        /**
         * Returns the division of this components by another vector.
         *
         * \warning
         * If other vector has a zero component, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF3 operator/(VectF3 const& v) const;

        /**
         * Returns the addition of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF3 operator+(float const s) const;

        /**
         * Returns a new vector addition of this vector with v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF3 operator+(VectF3 const& v) const;

        /**
         * Returns the subtraction of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF3 operator-(float const s) const;

        /**
         * Returns a new vector subtraction of this vector by v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF3 operator-(VectF3 const& v) const;

        /**
         * Multiplies this by a scalar.
         *
         * param s The scalar value.
         * \return Reference to the current vector after multiplication.
         */
        VectF3& operator*=(float const s);

        /**
         * Multiplies this by a vector.
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF3& operator*=(VectF3 const& v);

        /**
         * Divides this by a scalar.
         *
         * \warning
         * If scalar is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * param s The scalar value.
         * \return Reference to the current vector after division.
         */
        VectF3& operator/=(float const s);

        /**
         * Divides this by a vector.
         *
         * \warning
         * If other vector has a zero component, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF3& operator/=(VectF3 const& v);

        /**
         * Adds a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after addition.
         */
        VectF3& operator+=(VectF3 const& v);

        /**
         * Adds a scalar to each this components.
         *
         * \param s Scalar value.
         * \return Reference to the current vector after addition.
         */
        VectF3& operator+=(float const s);

        /**
         * Subtracts a scalar to each this components.
         *
         * \param v Scalar value.
         * \return Reference to the current vector after subtraction.
         */
        VectF3& operator-=(float const s);

        /**
         * Subtracts a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after subtraction.
         */
        VectF3& operator-=(VectF3 const& v);

        /**
         * Checks equality of 2 vectors.
         *
         * \param v The other vector.
         * \return True if both vectors have same component values, otherwise, return false.
         */
        bool operator==(VectF3 const& v) const;

        /**
         * Checks inequality of the 2 vectors.
         *
         * \param v The other vector.
         * \return True if not equal, otherwise, return false.
         */
        bool operator!=(VectF3 const& v) const;

        /**
         * Gets a copy of the component at requested position.
         *
         * \warning
         * Index must be in range, otherwise this function will crash.
         * For performance raison, no check is done.
         *
         * \return Copy of component v[index].
         */
        float operator[](const size_t index) const;

        /**
         * Gets a reference to the  component at requested position.
         *
         * \warning
         * Index must be in range, otherwise this function will crash.
         * For performance raison, no check is done.
         *
         * \return Reference to component v[index].
         */
        float& operator[](const size_t index);

        /**
         * Writes a simple string representation of the vector.
         *
         * \param os Stream where to write.
         * \param v Vector print.
         */
        friend std::ostream& operator<<(std::ostream& os, VectF3 const& v);

#ifdef __SSE4_1__
// Required if SSE is used (Works with 16 bytes aligned memories. Type __m128)
} GCC_ALIGNED(16);
#else
};
#endif


#include "VectF3.inl"

#endif // #ifndef _VECTF3_H_
