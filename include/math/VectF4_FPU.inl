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
// INLINE.
// FPU Implementation. This is the common Vector implementation.
// Author: Constantin M.
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4::VectF4() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

FORCE_INLINE VectF4::VectF4(const float s) {
    this->x = s;
    this->y = s;
    this->z = s;
    this->w = s;
}

FORCE_INLINE VectF4::VectF4(const float x,
                            const float y,
                            const float z,
                            const float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::length() const {
    return sqrt(this->squareLength());
}

FORCE_INLINE float VectF4::length3() const {
    return sqrt(this->squareLength3());
}

FORCE_INLINE float VectF4::squareLength() const {
    return (x*x) + (y*y) + (z*z) + (w*w);
}

FORCE_INLINE float VectF4::squareLength3() const {
    return (x*x) + (y*y) + (z*z);
}

FORCE_INLINE VectF4 VectF4::getNormalFast() const {
    float l = this->length();
    VectF4 v(x/l, y/l, z/l, w/l);
    return v;
}

FORCE_INLINE VectF4 VectF4::getNormalFast3() const {
    float l = this->length3();
    VectF4 v(x/l, y/l, z/l, 0.0f);
    return v;
}

FORCE_INLINE void VectF4::normalizeFast() {
    float l = this->length();
    this->set(x/l, y/l, z/l, w/l);
}

FORCE_INLINE VectF4 VectF4::getCrossProduct(VectF4 const& v) const {
    return VectF4(
        (y * v.z) - (z * v.y),
        (z * v.x) - (x * v.z),
        (x * v.y) - (y * v.x),
        0.0f
    );
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

FORCE_INLINE float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

FORCE_INLINE VectF4 VectF4::crossProduct(VectF4 const& v1, VectF4 const& v2) {
    return VectF4(
        (v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x),
        0.0f
    );
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF4::set(float const x,
                              float const y,
                              float const z,
                              float const w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

FORCE_INLINE void VectF4::set(VectF4 const& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4 VectF4::operator*(float const s) const {
    return VectF4(x*s, y*s, z*s, w*s);
}

FORCE_INLINE VectF4 VectF4::operator*(VectF4 const& v) const {
    return VectF4(x*v.x, y*v.y, z*v.z, w*v.w);
}

FORCE_INLINE VectF4 VectF4::operator/(float const s) const {
    return VectF4(x/s, y/s, z/s, w/s);
}

FORCE_INLINE VectF4 VectF4::operator/(VectF4 const& v) const {
    return VectF4(x/v.x, y/v.y, z/v.z, w/v.w);
}

FORCE_INLINE VectF4 VectF4::operator+(float const s) const {
    return VectF4(x+s, y+s, z+s, w+s);
}

FORCE_INLINE VectF4 VectF4::operator+(VectF4 const& v) const {
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
}

FORCE_INLINE VectF4 VectF4::operator-(float const s) const {
    return VectF4(x-s, y-s, z-s, w-s);
}

FORCE_INLINE VectF4 VectF4::operator-(VectF4 const& v) const {
    return VectF4(x-v.x, y-v.y, z-v.z, w-v.w);
}

FORCE_INLINE VectF4& VectF4::operator*=(float const s) {
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    this->w = this->w * s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator*=(VectF4 const& v) {
    this->x = this->x * v.x;
    this->y = this->y * v.y;
    this->z = this->z * v.z;
    this->w = this->w * v.w;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(float const s) {
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    this->w = this->w / s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(VectF4 const& v) {
    this->x = this->x / v.x;
    this->y = this->y / v.y;
    this->z = this->z / v.z;
    this->w = this->w / v.w;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(float const s) {
    this->x = this->x + s;
    this->y = this->y + s;
    this->z = this->z + s;
    this->w = this->w + s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(VectF4 const& v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    this->w = this->w + v.w;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(float const s) {
    this->x = this->x - s;
    this->y = this->y - s;
    this->z = this->z - s;
    this->w = this->w - s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(VectF4 const& v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    this->w = this->w - v.w;
    return *this;
}

FORCE_INLINE bool VectF4::operator==(VectF4 const& v) const {
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
}

FORCE_INLINE bool VectF4::operator!=(VectF4 const& v) const {
    return !(*this == v);
}

