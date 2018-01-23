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
 * \author  Constantin Masson
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
