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

#ifndef _MATRIXF4_H_
#define _MATRIXF4_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF4.h"
#include "math/MatrixF3.h"


/**
 * A 4x4 matrix with floating point precision.
 *
 * \remarks
 * Matrix multiplication with Vector use a 'Column vector' transformation.
 * This means a multiplication with a vector V is done in the right-to-left order.
 * For instance, M1 * M2 * M3 * V1 will actually calculate M3 * V1 first.
 *
 * This is an illustration of the final calculation: (M1 * (M2 * (M3 * V1) ) )
 *
 * \par
 * Order is important since matrix multiplication is not commutative.
 * Right-to-left order is the common representation used by OpenGL for instance.
 *
 * \par
 * Matrix is stored contiguously in memory in a row fashion:
 * each row contains a single vector.
 *
 * \since:  Jun 24, 2017
 * \author: Constantin M.
 */
class MatrixF4
{
public:
        // ---------------------------------------------------------------------
        // Class members
        // ---------------------------------------------------------------------

        // Matrix indexed by [row][column]
        float _m[4][4] GCC_ALIGNED(16);

        /**
         * Identity matrix.
         * Matrix filled with 1 on its diagonal.
         *
         * \return New identity matrix.
         */
        static MatrixF4 IDENTITY();

        /**
         * Zero matrix.
         * Matrix filled with 0 everywhere!
         *
         * \return New zero matrix.
         */
        static MatrixF4 ZERO();


    public:
        // ---------------------------------------------------------------------
        // Constructors / Initialization
        // ---------------------------------------------------------------------

        /**
         * Create a new 4x4 matrix filled with zero.
         */
        MatrixF4();

        /**
         * Create a new 4x4 matrix with all components set to a specific value.
         *
         * \param value Matrix is filled with it.
         */
        explicit MatrixF4(const float value);

        /**
         * Create a new 4x4 matrix from 4 vectors.
         *
         * \param row1 Values for positions m[0][0] to m[0][3].
         * \param row2 Values for positions m[1][0] to m[1][3].
         * \param row3 Values for positions m[2][0] to m[2][3].
         * \param row4 Values for positions m[3][0] to m[3][3].
         */
        explicit MatrixF4(VectF4 const& row1,
                          VectF4 const& row2,
                          VectF4 const& row3,
                          VectF4 const& row4);

        /**
         * Create a new 4x4 matrix with each component explicitly set.
         *
         * \param m00 Component at Row 0 Column 0.
         * \param m01 Component at Row 0 Column 1.
         * \param m02 Component at Row 0 Column 2.
         * \param m03 Component at Row 0 Column 3.
         *
         * \param m10 Component at Row 1 Column 0.
         * \param m11 Component at Row 1 Column 1.
         * \param m12 Component at Row 1 Column 2.
         * \param m13 Component at Row 1 Column 3.
         *
         * \param m20 Component at Row 2 Column 0.
         * \param m21 Component at Row 2 Column 1.
         * \param m22 Component at Row 2 Column 2.
         * \param m23 Component at Row 2 Column 3.
         *
         * \param m30 Component at Row 3 Column 0.
         * \param m31 Component at Row 3 Column 1.
         * \param m32 Component at Row 3 Column 2.
         * \param m33 Component at Row 3 Column 3.
         */
        explicit MatrixF4(
            const float m00, const float m01, const float m02, const float m03,
            const float m10, const float m11, const float m12, const float m13,
            const float m20, const float m21, const float m22, const float m23,
            const float m30, const float m31, const float m32, const float m33);

        /**
         * Create a new 4x4 matrix from a 3x3.
         *
         * \remark
         * A 4x4 matrix can be partitioned into 4 components.
         * The upper 3x3 matrix U.
         * The 1x3 translation vector t.
         * The 3x1 vector of 0.
         * And the scalar 1 at the bottom right.
         *
         * \par
         * The given 3x3 is the U matrix.
         * Translation vector is set to 0 and scalar is set to 1.
         *
         * \par
         * This is the case of Column vector convention.
         * \see MatrixF4 documentation for remind about the used Matrix representation.
         *
         */
        explicit MatrixF4(MatrixF3 const& m3);


    public:
        // ---------------------------------------------------------------------
        // Class functions
        // ---------------------------------------------------------------------

        /**
         * Returns the transposition of this matrix.
         * Transposition is the matrix where m[i][j] = this[j][i].
         *
         * \return New Transposition matrix.
         */
        MatrixF4 getTransposition() const;

        /**
         * Transpose this matrix in place.
         * Transposition is the matrix where m[i][j] = this[j][i].
         */
        void transpose();


    public:
        // ---------------------------------------------------------------------
        // Getters / Setters
        // ---------------------------------------------------------------------

        /**
         * Set this matrix values from another matrix.
         *
         * \param m The other matrix to copy.
         */
        void set(MatrixF4 const& m);


    public:
        // ---------------------------------------------------------------------
        // Operators overload
        // ---------------------------------------------------------------------

        /**
         * Multiplies this matrix by a scalar and returns the new matrix.
         * Each this component is multiplied by s.
         *
         * \param s Scalar.
         * \return New matrix multiplied by the scalar s.
         */
        MatrixF4 operator*(float const s) const;

        /**
         * Multiplies the matrix with a Vector and returns the new Vector.
         * Use row vector representation, so multiplication is done in Right to Left order.
         * (See remark for several informations).
         *
         * \param v Vector to multiply with.
         * \return New vector V2 = matrix * v.
         */
        VectF4 operator*(VectF4 const& v) const;

        /**
         * Multiplies this matrix with another and returns a new matrix.
         *
         * \param m Matrix to multiply with.
         * \return New matrix resulting from the multiplication (this * m).
         */
        MatrixF4 operator*(MatrixF4 const& m) const;

        /**
         * Multiplies in place this matrix with a scalar.
         *
         * \param s Scalar.
         * \return Reference to this.
         */
        MatrixF4& operator*=(float const s);

        /**
         * Multiplies in place this matrix with another.
         *
         * \param m The other matrix.
         * \return Reference to this.
         */
        MatrixF4& operator*=(MatrixF4 const& m);


        /**
         * Test equality of 2 matrix.
         * This test if both matrix contains same values.
         * (Does not check if matrix are the same memory entity).
         *
         * \param m Matrix to test with.
         * \return True if this == m, otherwise, return false.
         */
        bool operator==(MatrixF4 const& m) const;

        /**
         * Test inequality of 2 matrix.
         * False as soon as at least one value is not equal.
         *
         * \param m Matrix to test with.
         * \return True if this != m, otherwise, return false.
         */
        bool operator!=(MatrixF4 const& m) const;
};


#include "MatrixF4.inl"

#endif // #ifndef _MATRIXF4_H_
