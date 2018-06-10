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
// Abstract:            a definition of class 'Engine'
//
// Usage:               none
//
// Version:             0.0.2

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
        Camera cctv;
        float depthBuffer[WINDOW_DEFAULT_SIZE_W * WINDOW_DEFAULT_SIZE_H];

    public:
        bool init();
        bool initMesh(const char*);
        bool startRendering();
        bool stopRendering();
        void destroy();

    private:
        bool renderOneFrame();
        void renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes);
        void renderAll_xyz(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes/*, float, float, float*/);
        void handleEvent(SDL_Event* sdlevent);

    private:
	int	iChanged = 0;
	float	fX, fY, fZ;
	float	fStep = 3.1415;

};

#endif // #ifndef _ENGINE_H
