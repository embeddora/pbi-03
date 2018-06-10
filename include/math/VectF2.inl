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
// Vector 2 function definitions.
// Author: Constantin M.
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF2::VectF2() {
    this->x = 0.0f;
    this->y = 0.0f;
}

FORCE_INLINE VectF2::VectF2(const float s) {
    this->x = s;
    this->y = s;
}

FORCE_INLINE VectF2::VectF2(const float x, const float y) {
    this->x = x;
    this->y = y;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF2::length() const {
    return sqrt(this->squareLength());
}

FORCE_INLINE float VectF2::squareLength() const {
    return (x*x) + (y*y);
}

FORCE_INLINE VectF2 VectF2::getNormalFast() const {
    float l = this->length();
    VectF2 v(x/l, y/l);
    return v;
}

FORCE_INLINE void VectF2::normalizeFast() {
    float l = this->length();
    this->set(x/l, y/l);
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF2::dotProduct(VectF2 const& v1, VectF2 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF2::set(float const x, float const y) {
    this->x = x;
    this->y = y;
}

FORCE_INLINE void VectF2::set(VectF2 const& v) {
    this->x = v.x;
    this->y = v.y;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF2 VectF2::operator*(float const s) const {
    return VectF2(x*s, y*s);
}

FORCE_INLINE VectF2 VectF2::operator*(VectF2 const& v) const {
    return VectF2(x*v.x, y*v.y);
}

FORCE_INLINE VectF2 VectF2::operator/(float const s) const {
    return VectF2(x/s, y/s);
}

FORCE_INLINE VectF2 VectF2::operator/(VectF2 const& v) const {
    return VectF2(x/v.x, y/v.y);
}

FORCE_INLINE VectF2 VectF2::operator+(float const s) const {
    return VectF2(x+s, y+s);
}

FORCE_INLINE VectF2 VectF2::operator+(VectF2 const& v) const {
    return VectF2(x+v.x, y+v.y);
}

FORCE_INLINE VectF2 VectF2::operator-(float const s) const {
    return VectF2(x-s, y-s);
}

FORCE_INLINE VectF2 VectF2::operator-(VectF2 const& v) const {
    return VectF2(x-v.x, y-v.y);
}

FORCE_INLINE VectF2& VectF2::operator*=(float const s) {
    this->x = this->x * s;
    this->y = this->y * s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator*=(VectF2 const& v) {
    this->x = this->x * v.x;
    this->y = this->y * v.y;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator/=(float const s) {
    this->x = this->x / s;
    this->y = this->y / s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator/=(VectF2 const& v) {
    this->x = this->x / v.x;
    this->y = this->y / v.y;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator+=(float const s) {
    this->x = this->x + s;
    this->y = this->y + s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator+=(VectF2 const& v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator-=(float const s) {
    this->x = this->x - s;
    this->y = this->y - s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator-=(VectF2 const& v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    return *this;
}

FORCE_INLINE bool VectF2::operator==(VectF2 const& v) const {
    return this->x == v.x && this->y == v.y;
}

FORCE_INLINE bool VectF2::operator!=(VectF2 const& v) const {
    return !(*this == v);
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF2 const& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

FORCE_INLINE float VectF2::operator[](const size_t index) const {
    return (&x)[index];
}

FORCE_INLINE float& VectF2::operator[](const size_t index){
    return (&x)[index];
}

