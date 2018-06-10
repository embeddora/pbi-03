//
// Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//        * Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//        * Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the distribution.
//        * Neither the name of The Linux Foundation nor
//          the names of its contributors may be used to endorse or promote
//          products derived from this software without specific prior written
//          permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Abstract:            none
//
// Usage:               none
//
// Version:             0.0.2

#ifndef _VECTF2_H_
#define _VECTF2_H_

#include <iostream>
#include <cmath>

#include "core/config.h"


/**
 * 2 Dimensions vector with floating point precision.
 *
 * \since   Aug 4, 2017
 * \author  Constantin M.
 */
class VectF2 {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    public:
        float x;
        float y;

    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        /**
         * Create a new null vector (All components to 0).
         */
        VectF2();

        /**
         * Create initialized vector.
         *
         * \param x The x value to set.
         * \param y The y value to set.
         */
        explicit VectF2(const float x, const float y);

        /**
         * Create initialized vector.
         * Each components are set with the given value.
         *
         * \param s Value to set for all components.
         */
        explicit VectF2(const float s);


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
        VectF2 getNormalFast() const;

        /**
         * Normalize this vector in place.
         *
         * \warning
         * If vector length is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         */
        void normalizeFast();


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
        static float dotProduct(VectF2 const& v1, VectF2 const& v2);


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:
        /**
         * Sets all axis values of this.
         *
         * \param x New x coordinate.
         * \param y New y coordinate.
         */
        void set(float const x, float const y);

        /**
         * Copy values of the given vector in this.
         *
         * \param v Vector to use as copy.
         */
        void set(VectF2 const& v);


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
        VectF2 operator*(float const s) const;

        /**
         * Returns the multiplication of this by another vector.
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF2 operator*(VectF2 const& v) const;

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
        VectF2 operator/(float const s) const;

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
        VectF2 operator/(VectF2 const& v) const;

        /**
         * Returns the addition of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF2 operator+(float const s) const;

        /**
         * Returns a new vector addition of this vector with v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF2 operator+(VectF2 const& v) const;

        /**
         * Returns the subtraction of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF2 operator-(float const s) const;

        /**
         * Returns a new vector subtraction of this vector by v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF2 operator-(VectF2 const& v) const;

        /**
         * Multiplies this by a scalar.
         *
         * param s The scalar value.
         * \return Reference to the current vector after multiplication.
         */
        VectF2& operator*=(float const s);

        /**
         * Multiplies this by a vector.
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF2& operator*=(VectF2 const& v);

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
        VectF2& operator/=(float const s);

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
        VectF2& operator/=(VectF2 const& v);

        /**
         * Adds a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after addition.
         */
        VectF2& operator+=(VectF2 const& v);

        /**
         * Adds a scalar to each this components.
         *
         * \param s Scalar value.
         * \return Reference to the current vector after addition.
         */
        VectF2& operator+=(float const s);

        /**
         * Subtracts a scalar to each this components.
         *
         * \param v Scalar value.
         * \return Reference to the current vector after subtraction.
         */
        VectF2& operator-=(float const s);

        /**
         * Subtracts a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after subtraction.
         */
        VectF2& operator-=(VectF2 const& v);

        /**
         * Checks equality of 2 vectors.
         *
         * \param v The other vector.
         * \return True if both vectors have same component values, otherwise, return false.
         */
        bool operator==(VectF2 const& v) const;

        /**
         * Checks inequality of the 2 vectors.
         *
         * \param v The other vector.
         * \return True if not equal, otherwise, return false.
         */
        bool operator!=(VectF2 const& v) const;

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
        friend std::ostream& operator<<(std::ostream& os, VectF2 const& v);
};


#include "VectF2.inl"

#endif // #ifndef _VECTF2_H_
