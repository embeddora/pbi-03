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
// Abstract:            a definition of class 'MeshManager'
//
// Usage:               none
//
// Version:             0.0.8

#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#include <fstream>

#include <stdlib.h>

#include <boost/property_tree/ptree.hpp>

#include <boost/property_tree/json_parser.hpp>

#include "Mesh.h"

#include "Singleton.h"


/**
 * Singleton manager for meshes.
 *
 * \since   August 2017
 * \author  Constantin M.
 */
class MeshManager : private Singleton<MeshManager>
{
    public:
        // ---------------------------------------------------------------------
        // Attributes
        // ---------------------------------------------------------------------

        /** List of all loaded meshes. */
        std::vector<Mesh> listMeshes; // TODO Change to private

    private:
        /** Keep track if manager has been initialized. */
        bool isInitialized;


        // ---------------------------------------------------------------------
        // Singleton Override
        // ---------------------------------------------------------------------
    private:
        MeshManager();
        friend Singleton<MeshManager>;

    public:
        using Singleton<MeshManager>::getInstance;
        using Singleton<MeshManager>::getInstancePtr;

    public:
        // ---------------------------------------------------------------------
        // Init methods
        // ---------------------------------------------------------------------

        /**
         * Initialize the MeshManager.
         * Should be called once at the beginning.
         * Do nothing if already already called.
         */
        void startUp();

        /**
         * Stop and clean the MeshManager.
         * Should be called once at the end.
         * Do nothing if already already called.
         */
        void shutDown();

    public:
        // ---------------------------------------------------------------------
        // Class methods
        // ---------------------------------------------------------------------

        /**
         * Load meshes from a Babylone JSON file.
         * If successfully loaded, add meshes in list of registered meshes.
         *
         * \see
         * https://doc.babylonjs.com/generals/file_format_map_(.babylon)#meshes
         *
         * \param file File to load.
         */
        void loadMeshesFromJSON(const char* file);
};

#endif // #ifndef _MESHMANAGER_H_
