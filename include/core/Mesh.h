/*
 * Copyright (C) 2018 ARNERI arneri@ukr.net All rights reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Abstract: 
 */

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
 * \author  Constantin Masson
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
