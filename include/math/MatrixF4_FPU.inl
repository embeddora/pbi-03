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

// =============================================================================
// INLINE MATRIX
// Contains FPU implementation of matrix functions.
// Author: Constantin M.
//
// TODO: refactoring
// There are probably several duplicates and not optimized thing (Code size...).
// It's ok for now, but refactoring may be a good idea later.
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors - Initialization
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4::MatrixF4() {
    _m[0][0] = _m[0][1] = _m[0][2] = _m[0][3] = 0.0f;
    _m[1][0] = _m[1][1] = _m[1][2] = _m[1][3] = 0.0f;
    _m[2][0] = _m[2][1] = _m[2][2] = _m[2][3] = 0.0f;
    _m[3][0] = _m[3][1] = _m[3][2] = _m[3][3] = 0.0f;
}

FORCE_INLINE MatrixF4::MatrixF4(const float value) {
    _m[0][0] = _m[0][1] = _m[0][2] = _m[0][3] = value;
    _m[1][0] = _m[1][1] = _m[1][2] = _m[1][3] = value;
    _m[2][0] = _m[2][1] = _m[2][2] = _m[2][3] = value;
    _m[3][0] = _m[3][1] = _m[3][2] = _m[3][3] = value;
}

FORCE_INLINE MatrixF4::MatrixF4(VectF4 const& row1,
                                VectF4 const& row2,
                                VectF4 const& row3,
                                VectF4 const& row4) {
    // Row 1
    _m[0][0] = row1.x;
    _m[0][1] = row1.y;
    _m[0][2] = row1.z;
    _m[0][3] = row1.w;
    // Row 2
    _m[1][0] = row2.x;
    _m[1][1] = row2.y;
    _m[1][2] = row2.z;
    _m[1][3] = row2.w;
    // Row 3
    _m[2][0] = row3.x;
    _m[2][1] = row3.y;
    _m[2][2] = row3.z;
    _m[2][3] = row3.w;
    // Row 4
    _m[3][0] = row4.x;
    _m[3][1] = row4.y;
    _m[3][2] = row4.z;
    _m[3][3] = row4.w;
}

FORCE_INLINE MatrixF4::MatrixF4(
        const float m00, const float m01, const float m02, const float m03,
        const float m10, const float m11, const float m12, const float m13,
        const float m20, const float m21, const float m22, const float m23,
        const float m30, const float m31, const float m32, const float m33) {
    // Row 1
    this->_m[0][0] = m00;
    this->_m[0][1] = m01;
    this->_m[0][2] = m02;
    this->_m[0][3] = m03;
    // Row 2
    this->_m[1][0] = m10;
    this->_m[1][1] = m11;
    this->_m[1][2] = m12;
    this->_m[1][3] = m13;
    // Row 3
    this->_m[2][0] = m20;
    this->_m[2][1] = m21;
    this->_m[2][2] = m22;
    this->_m[2][3] = m23;
    // Row 4
    this->_m[3][0] = m30;
    this->_m[3][1] = m31;
    this->_m[3][2] = m32;
    this->_m[3][3] = m33;
}

FORCE_INLINE MatrixF4::MatrixF4(MatrixF3 const& m3){
    // Row 1
    this->_m[0][0] = m3._m[0][0];
    this->_m[0][1] = m3._m[0][1];
    this->_m[0][2] = m3._m[0][2];
    this->_m[0][3] = 0.0f;
    // Row 2
    this->_m[1][0] = m3._m[1][0];
    this->_m[1][1] = m3._m[1][1];
    this->_m[1][2] = m3._m[1][2];
    this->_m[1][3] = 0.0f;
    // Row 3
    this->_m[2][0] = m3._m[2][0];
    this->_m[2][1] = m3._m[2][1];
    this->_m[2][2] = m3._m[2][2];
    this->_m[2][3] = 0.0f;
    // Row 4
    this->_m[3][0] = 0.0f;
    this->_m[3][1] = 0.0f;
    this->_m[3][2] = 0.0f;
    this->_m[3][3] = 1.0f;
}



// -----------------------------------------------------------------------------
// class functions
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4 MatrixF4::getTransposition() const {
    MatrixF4 nMatrix;
    // TODO Note: I have to check, but compiler might optimize this to remove loop
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            nMatrix._m[i][j] = _m[j][i];
        }
    }
    return nMatrix;
}

FORCE_INLINE void MatrixF4::transpose() {
    MatrixF4 m = this->getTransposition();
    this->set(m);
}


// -----------------------------------------------------------------------------
// Operators overload (General)
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4 MatrixF4::operator*(float const s) const {
    MatrixF4 nMatrix;
    // Row 1
    nMatrix._m[0][0] = _m[0][0] * s;
    nMatrix._m[0][1] = _m[0][1] * s;
    nMatrix._m[0][2] = _m[0][2] * s;
    nMatrix._m[0][3] = _m[0][3] * s;
    // Row 2
    nMatrix._m[1][0] = _m[1][0] * s;
    nMatrix._m[1][1] = _m[1][1] * s;
    nMatrix._m[1][2] = _m[1][2] * s;
    nMatrix._m[1][3] = _m[1][3] * s;
    // Row 3
    nMatrix._m[2][0] = _m[2][0] * s;
    nMatrix._m[2][1] = _m[2][1] * s;
    nMatrix._m[2][2] = _m[2][2] * s;
    nMatrix._m[2][3] = _m[2][3] * s;
    // Row 4
    nMatrix._m[3][0] = _m[3][0] * s;
    nMatrix._m[3][1] = _m[3][1] * s;
    nMatrix._m[3][2] = _m[3][2] * s;
    nMatrix._m[3][3] = _m[3][3] * s;
    return nMatrix;
}

FORCE_INLINE VectF4 MatrixF4::operator*(VectF4 const& v) const {
    VectF4 nVect;
    nVect.x = _m[0][0] * v.x + _m[0][1] * v.y + _m[0][2] * v.z + _m[0][3] * v.w;
    nVect.y = _m[1][0] * v.x + _m[1][1] * v.y + _m[1][2] * v.z + _m[1][3] * v.w;
    nVect.z = _m[2][0] * v.x + _m[2][1] * v.y + _m[2][2] * v.z + _m[2][3] * v.w;
    nVect.w = _m[3][0] * v.x + _m[3][1] * v.y + _m[3][2] * v.z + _m[3][3] * v.w;
    return nVect;
}

FORCE_INLINE MatrixF4 MatrixF4::operator*(MatrixF4 const& o) const {
    MatrixF4 nMatrix;
    // Row 1
    nMatrix._m[0][0] = _m[0][0] * o._m[0][0] + _m[0][1] * o._m[1][0] + _m[0][2] * o._m[2][0] + _m[0][3] * o._m[3][0];
    nMatrix._m[0][1] = _m[0][0] * o._m[0][1] + _m[0][1] * o._m[1][1] + _m[0][2] * o._m[2][1] + _m[0][3] * o._m[3][1];
    nMatrix._m[0][2] = _m[0][0] * o._m[0][2] + _m[0][1] * o._m[1][2] + _m[0][2] * o._m[2][2] + _m[0][3] * o._m[3][2];
    nMatrix._m[0][3] = _m[0][0] * o._m[0][3] + _m[0][1] * o._m[1][3] + _m[0][2] * o._m[2][3] + _m[0][3] * o._m[3][3];
    // Row 2
    nMatrix._m[1][0] = _m[1][0] * o._m[0][0] + _m[1][1] * o._m[1][0] + _m[1][2] * o._m[2][0] + _m[1][3] * o._m[3][0];
    nMatrix._m[1][1] = _m[1][0] * o._m[0][1] + _m[1][1] * o._m[1][1] + _m[1][2] * o._m[2][1] + _m[1][3] * o._m[3][1];
    nMatrix._m[1][2] = _m[1][0] * o._m[0][2] + _m[1][1] * o._m[1][2] + _m[1][2] * o._m[2][2] + _m[1][3] * o._m[3][2];
    nMatrix._m[1][3] = _m[1][0] * o._m[0][3] + _m[1][1] * o._m[1][3] + _m[1][2] * o._m[2][3] + _m[1][3] * o._m[3][3];
    // Row 3
    nMatrix._m[2][0] = _m[2][0] * o._m[0][0] + _m[2][1] * o._m[1][0] + _m[2][2] * o._m[2][0] + _m[2][3] * o._m[3][0];
    nMatrix._m[2][1] = _m[2][0] * o._m[0][1] + _m[2][1] * o._m[1][1] + _m[2][2] * o._m[2][1] + _m[2][3] * o._m[3][1];
    nMatrix._m[2][2] = _m[2][0] * o._m[0][2] + _m[2][1] * o._m[1][2] + _m[2][2] * o._m[2][2] + _m[2][3] * o._m[3][2];
    nMatrix._m[2][3] = _m[2][0] * o._m[0][3] + _m[2][1] * o._m[1][3] + _m[2][2] * o._m[2][3] + _m[2][3] * o._m[3][3];
    // Row 4
    nMatrix._m[3][0] = _m[3][0] * o._m[0][0] + _m[3][1] * o._m[1][0] + _m[3][2] * o._m[2][0] + _m[3][3] * o._m[3][0];
    nMatrix._m[3][1] = _m[3][0] * o._m[0][1] + _m[3][1] * o._m[1][1] + _m[3][2] * o._m[2][1] + _m[3][3] * o._m[3][1];
    nMatrix._m[3][2] = _m[3][0] * o._m[0][2] + _m[3][1] * o._m[1][2] + _m[3][2] * o._m[2][2] + _m[3][3] * o._m[3][2];
    nMatrix._m[3][3] = _m[3][0] * o._m[0][3] + _m[3][1] * o._m[1][3] + _m[3][2] * o._m[2][3] + _m[3][3] * o._m[3][3];
    return nMatrix;
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void MatrixF4::set(MatrixF4 const& o){
    // Row 1
    this->_m[0][0] = o._m[0][0];
    this->_m[0][1] = o._m[0][1];
    this->_m[0][2] = o._m[0][2];
    this->_m[0][3] = o._m[0][3];
    // Row 2
    this->_m[1][0] = o._m[1][0];
    this->_m[1][1] = o._m[1][1];
    this->_m[1][2] = o._m[1][2];
    this->_m[1][3] = o._m[1][3];
    // Row 3
    this->_m[2][0] = o._m[2][0];
    this->_m[2][1] = o._m[2][1];
    this->_m[2][2] = o._m[2][2];
    this->_m[2][3] = o._m[2][3];
    // Row 4
    this->_m[3][0] = o._m[3][0];
    this->_m[3][1] = o._m[3][1];
    this->_m[3][2] = o._m[3][2];
    this->_m[3][3] = o._m[3][3];
}


// -----------------------------------------------------------------------------
// Operators overload (Inplace)
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4& MatrixF4::operator*=(float const s) {
    // Row 1
    this->_m[0][0] = this->_m[0][0] * s;
    this->_m[0][1] = this->_m[0][1] * s;
    this->_m[0][2] = this->_m[0][2] * s;
    this->_m[0][3] = this->_m[0][3] * s;
    // Row 2
    this->_m[1][0] = this->_m[1][0] * s;
    this->_m[1][1] = this->_m[1][1] * s;
    this->_m[1][2] = this->_m[1][2] * s;
    this->_m[1][3] = this->_m[1][3] * s;
    // Row 3
    this->_m[2][0] = this->_m[2][0] * s;
    this->_m[2][1] = this->_m[2][1] * s;
    this->_m[2][2] = this->_m[2][2] * s;
    this->_m[2][3] = this->_m[2][3] * s;
    // Row 4
    this->_m[3][0] = this->_m[3][0] * s;
    this->_m[3][1] = this->_m[3][1] * s;
    this->_m[3][2] = this->_m[3][2] * s;
    this->_m[3][3] = this->_m[3][3] * s;
    return *this;
}

FORCE_INLINE MatrixF4& MatrixF4::operator*=(MatrixF4 const& o) {
    this->set(*this * o);
    return *this;
}


// -----------------------------------------------------------------------------
// Operators overload (Other)
// -----------------------------------------------------------------------------
FORCE_INLINE bool MatrixF4::operator==(MatrixF4 const& o) const {
    return
        _m[0][0] == o._m[0][0] && _m[0][1] == o._m[0][1] && _m[0][2] == o._m[0][2] && _m[0][3] == o._m[0][3] &&
        _m[1][0] == o._m[1][0] && _m[1][1] == o._m[1][1] && _m[1][2] == o._m[1][2] && _m[1][3] == o._m[1][3] &&
        _m[2][0] == o._m[2][0] && _m[2][1] == o._m[2][1] && _m[2][2] == o._m[2][2] && _m[2][3] == o._m[2][3] &&
        _m[3][0] == o._m[3][0] && _m[3][1] == o._m[3][1] && _m[3][2] == o._m[3][2] && _m[3][3] == o._m[3][3];
}

FORCE_INLINE bool MatrixF4::operator!=(MatrixF4 const& o) const {
    return !(*this == o);
}


