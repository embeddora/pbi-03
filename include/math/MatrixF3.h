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

#ifndef _MATRIXF3_H_
#define _MATRIXF3_H_

#include "core/config.h"

#include "core/debug.h"

#include "math/VectF3.h"


/**
 * A 3x3 matrix with floating point precision.
 *
 * \remarks
 * Matrix is stored contiguously in memory in a row fashion:
 * each row contains a single vector.
 *
 * \remarks
 * For further information about matrix representation:
 * \see MatrixF4
 *
 * \note
 * TODO: currently not used except to create 4x4 matrix from 3x3.
 *
 * \since:  July 24, 2017
 * \author: Constantin M.
 */
class MatrixF3 {
    public:
        // ---------------------------------------------------------------------
        // Class members
        // ---------------------------------------------------------------------

        // Matrix indexed by [row][column]
        float _m[3][3]; // TODO See if alignment is needed here (GCC_ALIGN)

        /**
         * Identity matrix.
         * Matrix filled with 1 on its diagonal.
         *
         * \return New identity matrix.
         */
        static MatrixF3 IDENTITY();

        /**
         * Zero matrix.
         * Matrix filled with 0 everywhere!
         *
         * \return New zero matrix.
         */
        static MatrixF3 ZERO();


    public:
        // ---------------------------------------------------------------------
        // Constructors / Initialization
        // ---------------------------------------------------------------------
        MatrixF3();

        /**
         * Creates a new matrix filled by 3 rows.
         *
         * \param row1 Values for positions m[0][0] to m[0][2].
         * \param row2 Values for positions m[1][0] to m[1][2].
         * \param row3 Values for positions m[2][0] to m[2][2].
         */
        explicit MatrixF3(VectF3 const& row1,
                          VectF3 const& row2,
                          VectF3 const& row3);

        /**
         * Creates a new matrix with each component set respectively.
         *
         * \param m00 Component at Row 0 Column 0.
         * \param m01 Component at Row 0 Column 1.
         * \param m02 Component at Row 0 Column 2.
         *
         * \param m10 Component at Row 1 Column 0.
         * \param m11 Component at Row 1 Column 1.
         * \param m12 Component at Row 1 Column 2.
         *
         * \param m20 Component at Row 2 Column 0.
         * \param m21 Component at Row 2 Column 1.
         * \param m22 Component at Row 2 Column 2.
         */
        explicit MatrixF3(
            const float m00, const float m01, const float m02,
            const float m10, const float m11, const float m12,
            const float m20, const float m21, const float m22);

    public:
        // ---------------------------------------------------------------------
        // Class functions
        // ---------------------------------------------------------------------
        // TODO
};


#include "MatrixF3.inl"

#endif // #ifndef _MATRIXF3_H_
