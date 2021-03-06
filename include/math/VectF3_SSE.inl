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
    this->m128 = _mm_setzero_ps();
}

FORCE_INLINE VectF3::VectF3(const float s) {
    this->m128 = _mm_setr_ps(s,s,s,1.0f);
}

FORCE_INLINE VectF3::VectF3(const float x, const float y, const float z) {
    this->m128 = _mm_setr_ps(x,y,z,1.0f);
}

FORCE_INLINE VectF3::VectF3(const __m128 v) {
    this->m128 = v;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::length() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128, this->m128, 0x71)));
}

FORCE_INLINE float VectF3::squareLength() const {
    return _mm_cvtss_f32(_mm_dp_ps(this->m128, this->m128, 0x71));
}

FORCE_INLINE VectF3 VectF3::getNormalFast() const {
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0x7F));
    __m128 res  = _mm_div_ps(this->m128, l);
    res[3]      = 1.0f; // Set w to 1
    return VectF3(res);
}

FORCE_INLINE void VectF3::normalizeFast() {
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0x7F));
    __m128 res  = _mm_div_ps(this->m128, l);
    res[3]      = 1.0f; // Set w to 0
    this->set(res);
}

FORCE_INLINE VectF3 VectF3::getCrossProduct(VectF3 const& v) const {
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0.0f; // Set w to 0
    return VectF3(rabit);
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::dotProduct(VectF3 const& v1, VectF3 const& v2) {
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128, v2.m128, 0x71));
}

FORCE_INLINE VectF3 VectF3::crossProduct(VectF3 const& v1, VectF3 const& v2) {
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(v1.m128, v1.m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v2.m128, v2.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(v1.m128, v1.m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v2.m128, v2.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0.0f; // Set w to 0 (crossProduct only on 3 axis)
    return VectF3(rabit);
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF3::set(float const x, float const y, float const z) {
    this->m128 = _mm_setr_ps(x,y,z,1.0f);
}

FORCE_INLINE void VectF3::set(VectF3 const& v) {
    this->m128 = v.m128;
}

FORCE_INLINE void VectF3::set(const __m128 v) {
    this->m128 = v;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3 VectF3::operator*(float const s) const {
    return VectF3(_mm_mul_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF3 VectF3::operator*(VectF3 const& v) const {
    return VectF3(_mm_mul_ps(this->m128, v.m128));
}

FORCE_INLINE VectF3 VectF3::operator/(float const s) const {
    return VectF3(_mm_div_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF3 VectF3::operator/(VectF3 const& v) const {
    return VectF3(_mm_div_ps(this->m128, v.m128));
}

FORCE_INLINE VectF3 VectF3::operator+(float const s) const {
    return VectF3(_mm_add_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF3 VectF3::operator+(VectF3 const& v) const {
    return VectF3(_mm_add_ps(this->m128, v.m128));
}

FORCE_INLINE VectF3 VectF3::operator-(float const s) const {
    return VectF3(_mm_sub_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF3 VectF3::operator-(VectF3 const& v) const {
    return VectF3(_mm_sub_ps(this->m128, v.m128));
}

FORCE_INLINE VectF3& VectF3::operator*=(float const s) {
    this->m128 = _mm_mul_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator*=(VectF3 const& v) {
    this->m128 = _mm_mul_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(float const s) {
    this->m128 = _mm_div_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(VectF3 const& v) {
    this->m128 = _mm_div_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(float const s) {
    this->m128 = _mm_add_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(VectF3 const& v) {
    this->m128 = _mm_add_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(float const s) {
    this->m128 = _mm_sub_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(VectF3 const& v) {
    this->m128 = _mm_sub_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE bool VectF3::operator==(VectF3 const& v) const {
    __m128 res = _mm_cmpeq_ps(this->m128, v.m128);
    res[3] = 0xffffffff; // This is just in case of w has been altered (For any strange raison)
    return _mm_movemask_ps(res);
}

FORCE_INLINE bool VectF3::operator!=(VectF3 const& v) const {
    __m128 res = _mm_cmpneq_ps(this->m128, v.m128);
    res[3] = 0xffffffff; // This is just in case of w has been altered (For any strange raison)
    return _mm_movemask_ps(res);
}

