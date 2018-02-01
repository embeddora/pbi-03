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

#include <cstdlib>

#include <iostream>

#include "core/Engine.h"

int main(int argc, char**argv)
{
	/* Instantiate engine */
	Engine& engine = Engine::getInstance();

	/* Initialize SDL sybsystem and main window  */
	engine.init();

	/* Load mesh from file */
	engine.initMesh("resources/meshes/scene.cube");

	/* Cyclically process keys and draw a scene  */
	engine.startRendering();

	/* Load mesh from file */
	engine.initMesh("resources/meshes/scene.bicube");

	/* Cyclically process keys and draw a scene  */
	engine.startRendering();

	return EXIT_SUCCESS;
}
