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


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3::VectF3() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

FORCE_INLINE VectF3::VectF3(const float s) {
    this->x = s;
    this->y = s;
    this->z = s;
}

FORCE_INLINE VectF3::VectF3(const float x, const float y, const float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::length() const {
    return sqrt(this->squareLength());
}

FORCE_INLINE float VectF3::squareLength() const {
    return (x*x) + (y*y) + (z*z);
}

FORCE_INLINE VectF3 VectF3::getNormalFast() const {
    float l = this->length();
    VectF3 v(x/l, y/l, z/l);
    return v;
}

FORCE_INLINE void VectF3::normalizeFast() {
    float l = this->length();
    this->set(x/l, y/l, z/l);
}

FORCE_INLINE VectF3 VectF3::getCrossProduct(VectF3 const& v) const {
    return VectF3(
        (y * v.z) - (z * v.y),
        (z * v.x) - (x * v.z),
        (x * v.y) - (y * v.x)
    );
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::dotProduct(VectF3 const& v1, VectF3 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

FORCE_INLINE VectF3 VectF3::crossProduct(VectF3 const& v1, VectF3 const& v2) {
    return VectF3(
        (v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x)
    );
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF3::set(float const x, float const y, float const z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

FORCE_INLINE void VectF3::set(VectF3 const& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3 VectF3::operator*(float const s) const {
    return VectF3(x*s, y*s, z*s);
}

FORCE_INLINE VectF3 VectF3::operator*(VectF3 const& v) const {
    return VectF3(x*v.x, y*v.y, z*v.z);
}

FORCE_INLINE VectF3 VectF3::operator/(float const s) const {
    return VectF3(x/s, y/s, z/s);
}

FORCE_INLINE VectF3 VectF3::operator/(VectF3 const& v) const {
    return VectF3(x/v.x, y/v.y, z/v.z);
}

FORCE_INLINE VectF3 VectF3::operator+(float const s) const {
    return VectF3(x+s, y+s, z+s);
}

FORCE_INLINE VectF3 VectF3::operator+(VectF3 const& v) const {
    return VectF3(x+v.x, y+v.y, z+v.z);
}

FORCE_INLINE VectF3 VectF3::operator-(float const s) const {
    return VectF3(x-s, y-s, z-s);
}

FORCE_INLINE VectF3 VectF3::operator-(VectF3 const& v) const {
    return VectF3(x-v.x, y-v.y, z-v.z);
}

FORCE_INLINE VectF3& VectF3::operator*=(float const s) {
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator*=(VectF3 const& v) {
    this->x = this->x * v.x;
    this->y = this->y * v.y;
    this->z = this->z * v.z;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(float const s) {
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(VectF3 const& v) {
    this->x = this->x / v.x;
    this->y = this->y / v.y;
    this->z = this->z / v.z;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(float const s) {
    this->x = this->x + s;
    this->y = this->y + s;
    this->z = this->z + s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(VectF3 const& v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(float const s) {
    this->x = this->x - s;
    this->y = this->y - s;
    this->z = this->z - s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(VectF3 const& v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    return *this;
}

FORCE_INLINE bool VectF3::operator==(VectF3 const& v) const {
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z;
}

FORCE_INLINE bool VectF3::operator!=(VectF3 const& v) const {
    return !(*this == v);
}

