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

#include "core/Engine.h"



Engine::Engine() : renderWindow()
{
	this->isRunning = false;
}

bool Engine::init()
{
	MeshManager& meshManager = MeshManager::getInstance();

	meshManager.startUp();

//	meshManager.loadMeshesFromJSON("resources/meshes/scene");
	meshManager.loadMeshesFromJSON("resources/meshes/scene.bicube");

	this->cctv.position = VectF3(0.0f, 0.0f, -4.0f);

	this->cctv.target = meshManager.listMeshes[0].position;

	//Init SDL, TODO Dev Note: To export from Engine to a general 'init manager' or something like
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::clog << "[ERR] Unable to init Window. SDL_Error: " << SDL_GetError() << std::endl;

		return false;
	}

	renderWindow.initialize("3D soft Engine", WINDOW_DEFAULT_SIZE_W, WINDOW_DEFAULT_SIZE_H);

	renderWindow.show();

	return true;
}

void destroy()
{
    SDL_Quit();
}

bool Engine::startRendering()
{
	if(isRunning)
	{
		return false;
	}

	this->isRunning = true;

	// Main loop
	SDL_Event sdlevent;

	// TODO : DEV NOTE (To update with 'Elasped Time' system)
	// Currently, the game loop is a CPU-Dependent timer, meaning that it will
	// run faster on fast CPUs
	while(isRunning)
	{
		while(SDL_PollEvent(&sdlevent))
		{
			handleEvent(&sdlevent);
		}

		handleEvent(&sdlevent);

		renderOneFrame();
	}

	return true;
}

bool Engine::renderOneFrame()
{
	MeshManager& meshManager = MeshManager::getInstance();

	for(int k = 0; k < WINDOW_DEFAULT_SIZE_H * WINDOW_DEFAULT_SIZE_W; k++)
	{
		this->depthBuffer[k] = 2;
	}

	SDL_Renderer* renderer = this->renderWindow.sdl_renderer;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

//	this->renderAll(renderer, this->cctv, meshManager.listMeshes);
	this->renderAll_xyz(renderer, this->cctv, meshManager.listMeshes/*, this->fX, this->fY, this->fZ*/);

	SDL_RenderPresent(renderer);

	return true;
}

// Do a projection but don't project on screen, stay un frustum
static VectF3 projectPoint(VectF3 const& v, MatrixF4 const& m)
{
	VectF4 vec(v.x, v.y, v.z, 1.0f);

	vec = m * vec;

	vec /= vec.w;

	return VectF3(vec.x, vec.y, vec.z);
}

void Engine::renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes)
{
MatrixF4 viewMatrix;

MatrixF4 projectionMatrix;

const VectF3 up(0.0f, 1.0f, 0.0f);

const float w       = WINDOW_DEFAULT_SIZE_W;

const float h       = WINDOW_DEFAULT_SIZE_H;

	viewMatrix          = MatrixTransform::creaLookAtLH(camera.position, camera.target, up);

	projectionMatrix    = MatrixTransform::creaPerspectiveFovLH(1.57f, w, h, 1.0f, 45.0f);

	// Project each mesh
	for(Mesh & m : meshes)
	{
	const MatrixF4 posMatrix        = MatrixTransform::creaTranslate(m.position);

	const MatrixF4 rotMatrix        = MatrixTransform::creaRotateZYX(m.rotation);

	const MatrixF4 scaMatrix        = MatrixTransform::creaScale(m.scale);

	const MatrixF4 worldMatrix      = posMatrix * rotMatrix * scaMatrix;

	const MatrixF4 cameraMatrix     = viewMatrix * worldMatrix;

	const MatrixF4 transformMatrix  = projectionMatrix * cameraMatrix;

		for(auto & face : m.faces)
		{
			// Project 3 vertices in the 2D screen coordinates
			VectF3 p1_proj = MatrixTransform::projectOnScreen(m.vertices[face.a], transformMatrix, w, h);

			VectF3 p2_proj = MatrixTransform::projectOnScreen(m.vertices[face.b], transformMatrix, w, h);

			VectF3 p3_proj = MatrixTransform::projectOnScreen(m.vertices[face.c], transformMatrix, w, h);

			// Project normals in world coordinates
			VectF3 p1_norm = projectPoint(m.normals[face.a], worldMatrix);

			VectF3 p2_norm = projectPoint(m.normals[face.b], worldMatrix);

			VectF3 p3_norm = projectPoint(m.normals[face.c], worldMatrix);

			// Project positions in world coordinates
			VectF3 p1_pos = projectPoint(m.vertices[face.a], worldMatrix);

			VectF3 p2_pos = projectPoint(m.vertices[face.b], worldMatrix);

			VectF3 p3_pos = projectPoint(m.vertices[face.c], worldMatrix);

			VertexData v1 = {&p1_proj, &p1_norm, &p1_pos};

			VertexData v2 = {&p2_proj, &p2_norm, &p2_pos};

			VertexData v3 = {&p3_proj, &p3_norm, &p3_pos};

			// Color of the light (To refactor)
			SDL_Color color;

			color.r = 255;

			color.g = 240;

			color.b = 42;

			color.a = SDL_ALPHA_OPAQUE;

			DrawSDLUtils::drawGouraudTriangle(renderer, depthBuffer, v1, v2, v3, w, h, &color);

			//DrawSDLUtils::drawScanLineTriangle(renderer, depthBuffer, v1, v2, v3, w, h, &color);

			/* */
			SDL_SetRenderDrawColor(renderer, 92, 92, 92, SDL_ALPHA_OPAQUE);

			DrawSDLUtils::drawLine(renderer, p1_proj, p2_proj, w, h);
			DrawSDLUtils::drawLine(renderer, p2_proj, p3_proj, w, h);
			DrawSDLUtils::drawLine(renderer, p3_proj, p1_proj, w, h);
			/* */
		}

		/* m.rotation.x += 0.0025;
		m.rotation.y += 0.0025;
		m.rotation.z += 0.0025; */
	}
}


void Engine::renderAll_xyz(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes)
{
MatrixF4 viewMatrix;

MatrixF4 projectionMatrix;

const VectF3 up(0.0f, 1.0f, 0.0f);

const float w       = WINDOW_DEFAULT_SIZE_W;

const float h       = WINDOW_DEFAULT_SIZE_H;

	viewMatrix          = MatrixTransform::creaLookAtLH(camera.position, camera.target, up);

	projectionMatrix    = MatrixTransform::creaPerspectiveFovLH(1.57f, w, h, 1.0f, 45.0f);

	// Project each mesh
	for(Mesh & m : meshes)
	{
	const MatrixF4 posMatrix        = MatrixTransform::creaTranslate(m.position);

	const MatrixF4 rotMatrix        = MatrixTransform::creaRotateZYX(m.rotation);

	const MatrixF4 scaMatrix        = MatrixTransform::creaScale(m.scale);

	const MatrixF4 worldMatrix      = posMatrix * rotMatrix * scaMatrix;

	const MatrixF4 cameraMatrix     = viewMatrix * worldMatrix;

	const MatrixF4 transformMatrix  = projectionMatrix * cameraMatrix;

		for(auto & face : m.faces)
		{
			// Project 3 vertices in the 2D screen coordinates
			VectF3 p1_proj = MatrixTransform::projectOnScreen(m.vertices[face.a], transformMatrix, w, h);

			VectF3 p2_proj = MatrixTransform::projectOnScreen(m.vertices[face.b], transformMatrix, w, h);

			VectF3 p3_proj = MatrixTransform::projectOnScreen(m.vertices[face.c], transformMatrix, w, h);

			// Project normals in world coordinates
			VectF3 p1_norm = projectPoint(m.normals[face.a], worldMatrix);

			VectF3 p2_norm = projectPoint(m.normals[face.b], worldMatrix);

			VectF3 p3_norm = projectPoint(m.normals[face.c], worldMatrix);

			// Project positions in world coordinates
			VectF3 p1_pos = projectPoint(m.vertices[face.a], worldMatrix);

			VectF3 p2_pos = projectPoint(m.vertices[face.b], worldMatrix);

			VectF3 p3_pos = projectPoint(m.vertices[face.c], worldMatrix);

			VertexData v1 = {&p1_proj, &p1_norm, &p1_pos};

			VertexData v2 = {&p2_proj, &p2_norm, &p2_pos};

			VertexData v3 = {&p3_proj, &p3_norm, &p3_pos};

			// Color of the light (To refactor)
			SDL_Color color;

			color.r = 255;

			color.g = 240;

			color.b = 42;

			color.a = SDL_ALPHA_OPAQUE;

			if (1 == iChanged)
			{
				/* std::cout << "DO{" << fX << "," << fY << "," << fZ << "}" << std::endl;
				printf("<%p>\n", &fX); */
				if (0 != fX) { m.position.x += fStep*fX; }

				if (0 != fY) { m.position.y += fStep*fY; }

				if (0 != fZ) { m.position.z += fStep*fZ; }

				fX = fY = fZ = 0.0f; iChanged = 0;
				/* std::cout << "PS{" << fX << "," << fY << "," << fZ << "}" << std::endl;
				printf("<%p>\n", &fX); */
			}

			DrawSDLUtils::drawGouraudTriangle(renderer, depthBuffer, v1, v2, v3, w, h, &color);

			//DrawSDLUtils::drawScanLineTriangle(renderer, depthBuffer, v1, v2, v3, w, h, &color);

			/* */
			SDL_SetRenderDrawColor(renderer, 92, 92, 92, SDL_ALPHA_OPAQUE);

			DrawSDLUtils::drawLine(renderer, p1_proj, p2_proj, w, h);
			DrawSDLUtils::drawLine(renderer, p2_proj, p3_proj, w, h);
			DrawSDLUtils::drawLine(renderer, p3_proj, p1_proj, w, h);
			/* */
		}

		/*m.rotation.x += 0.0025;
		m.rotation.y += 0.0025;
		m.rotation.z += 0.0025;*/
	}
}

bool Engine::stopRendering()
{
	this->isRunning = false;

	return true;
}


void Engine::handleEvent(SDL_Event* sdlevent)
{
	switch (sdlevent->type)
	{
	case SDL_QUIT:

		std::cout << "(SDL_QUIT)" << std::endl;

		this->stopRendering();

		break;

	case SDL_MOUSEWHEEL:

#if 1
		cctv.position.z += sdlevent->wheel.y * 0.02f;
		std::cout << "(" << cctv.position.x << "," << cctv.position.y << "," << cctv.position.z << ")" << std::endl;
#endif /* (0) */

		break;


	case SDL_KEYDOWN:

		std::cout << "SDL_KEYDOWN" << std::endl;

		switch (sdlevent->key.keysym.sym) 
		{
			/* case SDLK_0: std::cout << "0 pressed" << std::endl; break;
			case SDLK_1: std::cout << "1 pressed" << std::endl; break;
			case SDLK_2: std::cout << "2 pressed" << std::endl; break;
			case SDLK_3: std::cout << "3 pressed" << std::endl; break;
			case SDLK_4: std::cout << "4 pressed" << std::endl; break;
			case SDLK_5: std::cout << "5 pressed" << std::endl; break;
			case SDLK_6: std::cout << "6 pressed" << std::endl; break;
			case SDLK_7: std::cout << "7 pressed" << std::endl; break;
			case SDLK_8: std::cout << "8 pressed" << std::endl; break;
			case SDLK_9: std::cout << "9 pressed" << std::endl; break; */

			case SDLK_a: { iChanged = 1; fX = -1;break; }
			case SDLK_f: { iChanged = 1; fX =  1;break; }
			case SDLK_e: { iChanged = 1; fY = -1;break; }
			case SDLK_c: { iChanged = 1; fY =  1;break; }
			case SDLK_m: { iChanged = 1; fZ = -1;break; } 
			case SDLK_n: { iChanged = 1; fZ =  1;break; }

			/* case SDLK_PAGEDOWN:  std::cout << "PDOWN" << std::endl; break;
			case SDLK_PAGEUP:    std::cout << "PUP" << std::endl; break;
			case SDLK_DOWN:      std::cout << "DOWN" << std::endl; break;
			case SDLK_UP:        std::cout << "UP" << std::endl; break;
			case SDLK_LEFT:      std::cout << "LEFT" << std::endl; break;
			case SDLK_RIGHT:     std::cout << "RIGHT" << std::endl; break; */

			default: break;
		}
		break;

	case SDL_KEYUP:
		break;

	case SDL_TEXTINPUT:
		/* std::cout << "(SDL_TEXTINPUT)" << std::endl;
		SDL_FlushEvent(SDL_TEXTINPUT); */
		break;
	}


}
