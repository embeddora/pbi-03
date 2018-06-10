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

#ifndef _DRAWSDLUTILS_H_
#define _DRAWSDLUTILS_H_

#include <SDL2/SDL.h>

#include <cmath>

#include "math/VectF3.h"


/**
 * Data for a vertices.
 */
typedef struct
{
	VectF3 *screenPos; // Position projected on the 2D screen

	VectF3 *normal; // Normal position in transformed coordinates

	VectF3 *transPos; // Position in transformed coordinates

} VertexData;


/**
 *
 * \note
 * TODO This class is temporary and will be re factored.
 * For now, it's pretty ugly :p
 * (Design pattern strategy + Factory for instance, to be able to switch used algorithm.)
 *
 * \note
 * These functions are mainly already implemented by SDL (And probably way better).
 * It is for the pure learning purpose.
 *
 * \see https://wiki.libsdl.org/SDL_RenderDrawLine
 */
class DrawSDLUtils {

    public:
        static void drawLine(SDL_Renderer* renderer, VectF3 const& p1, VectF3 const& p2, int w, int h);

        /**
         * Draw a line using Digital Differential Analyzer algorithm (DDA).
         *
         * \note
         * This isn't the most efficient algorithm since it still use one
         * floating point operation per pixel. But still better than naive
         * algorithm that uses 2 floating-point operations per pixel.
         */
        static void drawLineDDA(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int w, int h);

        static void drawScanLineTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        VertexData & v1,
                                        VertexData & v2,
                                        VertexData & v3,
                                        int w, int h,
                                        SDL_Color *color);

        static void drawGouraudTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        VertexData & v1,
                                        VertexData & v2,
                                        VertexData & v3,
                                        int w, int h,
                                        SDL_Color *color);

        static void drawScanLineTriangle(SDL_Renderer* renderer,
                                        int p1_x, int p1_y,
                                        int p2_x, int p2_y,
                                        int p3_x, int p3_y,
                                        int w, int h);

        static void drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h);
};

#endif // #ifndef _DRAWSDLUTILS_H_
