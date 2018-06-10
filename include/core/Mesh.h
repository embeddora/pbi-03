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
// Abstract:            a definition of class 'Mesh'
//
// Usage:               none
//
// Version:             0.0.2

#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

#include <string>

#include "math/VectF3.h"


// A face is a simple 3D triangle that constitutes a mesh.
typedef struct
{
	int a;

	int b;

	int c;
} Face;

/**
 * Mesh is used to represent a 3D object.
 * It is made of a set of vertices.
 *
 * \since   July 2017
 * \author  Constantin M.
 */
class Mesh
{
    public:
        /** The nice mesh's name */
        std::string name;

        /** Mesh's position in 3D world space */
        VectF3 position;

        /** Mesh's rotation */
        VectF3 rotation;

        /** Mesh's scale */
        VectF3 scale;

        /** All mesh's vertices */
        std::vector<VectF3> vertices;

        /** All normal vectors for vertices */
        std::vector<VectF3> normals;

        /** All faces */
        std::vector<Face> faces;

    public:
        Mesh();
        explicit Mesh(std::string name);
};

#endif // #ifndef _MESH_H_
