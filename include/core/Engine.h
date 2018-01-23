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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL2/SDL.h>

#include "core/Camera.h"

#include "core/Mesh.h"

#include "core/MeshManager.h"

#include "render/AppWindow.h"

#include "render/SDL2/AppWindowSDL2.h"

#include "render/SDL2/DrawSDLUtils.h"

#include "math/VectF2.h"

#include "math/VectF3.h"

#include "math/VectF4.h"

#include "math/MatrixF3.h"

#include "math/MatrixF4.h"

#include "math/MatrixTransform.h"

// TODO Probably to change later
// Default window value
#define WINDOW_DEFAULT_SIZE_W 960

#define WINDOW_DEFAULT_SIZE_H 540

/**
 * The core engine that runs the rendering.
 *
 * \warning
 * Alpha version subject to many changes.
 */
class Engine : private Singleton<Engine>
{
    private:
        Engine();
        friend Singleton<Engine>;

    public:
        using Singleton<Engine>::getInstance;
        using Singleton<Engine>::getInstancePtr;

    private:
        bool isRunning;
        AppWindowSDL2 renderWindow;

    private:
        // These variable are hard coded for now
        Camera cctv; // CCTV is watching you!
        float depthBuffer[WINDOW_DEFAULT_SIZE_W * WINDOW_DEFAULT_SIZE_H];

    public:
        bool init();
        bool startRendering();
        bool stopRendering();
        void destroy();

    private:
        bool renderOneFrame();
        void renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes);
        void handleEvent(SDL_Event* sdlevent);
};

#endif // #ifndef _ENGINE_H
