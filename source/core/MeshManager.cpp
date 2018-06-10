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

#include "core/MeshManager.h"

MeshManager::MeshManager()
{
	this->isInitialized = false;
}

void MeshManager::startUp()
{
	if(!isInitialized)
	{
		this->isInitialized = true;
	}
}

void MeshManager::shutDown()
{
	if(isInitialized)
	{
		this->isInitialized = false;

		this->listMeshes.clear();
	}
}

void MeshManager::loadMeshesFromJSON(const char* file)
{
using boost::property_tree::ptree;

using boost::property_tree::read_json;

ptree pt;

std::ifstream jsonFile(file);

	read_json(jsonFile, pt);

	// Load on mesh (File may define several)
	for(auto & child : pt.get_child("meshes"))
	{
	// name
	std::string name = child.second.get<std::string>("name", "NameNotFound");
	Mesh mesh(name); // The actual mesh to add

	// Position
	float positions[3];

	int index = 0;

		for(auto & position : child.second.get_child("position"))
		{
			std::string value = position.second.data();

			positions[index++] = ::atof(value.c_str());
		}
		mesh.position = VectF3(positions[0], positions[1], positions[2]);

		// Rotation
		float rotations[3];

		index = 0;

		for(auto & rotation : child.second.get_child("rotation"))
		{
			std::string value = rotation.second.data();

			rotations[index++] = ::atof(value.c_str());
		}
		mesh.rotation = VectF3(rotations[0], rotations[1], rotations[2]);

		// Scaling
		float scales[3];

		index = 0;

		for(auto & scale : child.second.get_child("scaling"))
		{
			std::string value = scale.second.data();

			scales[index++] = ::atof(value.c_str());
		}

		mesh.scale = VectF3(scales[0], scales[1], scales[2]);

		// Vertices + normals
		std::vector<float> listVertices;
		for(auto & vertice : child.second.get_child("vertices"))
		{
			std::string value = vertice.second.data();

			listVertices.push_back(::atof(value.c_str()));
		}
		int uvCount = child.second.get<int>("uvCount", 0); // Nb texture's coord per vertex

		// uvCount == 0 -> step 6 / 1 -> step 8 / 2 -> step 10
#if (0)
		int verticesPerStep = 6 + (uvCount * 2);
#else
		// TODO: resolve the hack. (Basically valid as lon as we don't use normals while drawing surfaces.) 
		int verticesPerStep = 3;
#endif /*  (0) */
		int nbVertices = listVertices.size() / verticesPerStep;

		for(int i = 0; i < nbVertices ; ++i)
		{
		VectF3 v(listVertices[i * verticesPerStep], listVertices[i * verticesPerStep + 1],	listVertices[i * verticesPerStep + 2]);

		VectF3 n(0.0,0.0,0.0);

			mesh.vertices.push_back(v);

			mesh.normals.push_back(n);
		}

		// Faces
		std::vector<float> listIndices;

		for(auto & indice : child.second.get_child("indices"))
		{
			std::string value = indice.second.data();

			listIndices.push_back(::atof(value.c_str()));
		}
		int nbFaces = listIndices.size() / 3;

		for(int i = 0; i < nbFaces; ++i)
		{
		Face face;

			face.a = listIndices[i * 3];

			face.b = listIndices[i * 3 + 1];

			face.c = listIndices[i * 3 + 2];

			mesh.faces.push_back(face);
		}

		// Register this mesh
		this->listMeshes.push_back(mesh);
	}
}
