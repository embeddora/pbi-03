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

#ifndef _APPWINDOWSDL2_H_
#define _APPWINDOWSDL2_H_

#include <iostream>

#include <SDL2/SDL.h>

#include "render/AppWindow.h"


/**
 * Render a Window using SDL2 
 *
 * \author  Constantin M.
 * \date    July 2017
 */
class AppWindowSDL2 : public AppWindow {
    public:
        //----------------------------------------------------------------------
        // Constants - Attributes
        //----------------------------------------------------------------------
        SDL_Window*     sdl_window; // The famous SDL window
        SDL_Renderer*   sdl_renderer; // Renderer for this window
        SDL_Texture*    sdl_texture; // Texture used with the renderer

    public:
        AppWindowSDL2();

    public:
        //----------------------------------------------------------------------
        // General functions
        //----------------------------------------------------------------------

        /** \copydoc AppWindow::initialize() */
        void initialize(const char* name, const int w, const int h, const int l, const int t);

        /** \copydoc AppWindow::initialize() */
        void initialize(const char* name, const int w, const int h);

        /** \copydoc AppWindow::show() */
        void show();

        /** \copydoc AppWindow::hide() */
        void hide();

        /** \copydoc AppWindow::destroy() */
        void destroy();

        /** \copydoc AppWindow::maximize() */
        void maximize();

        /** \copydoc AppWindow::minimize() */
        void minimize();

    public:
        //----------------------------------------------------------------------
        // Getter / Setters / Data
        //----------------------------------------------------------------------

        /** \copydoc AppWindow::getName() */
        const char* getName() const;

        /** \copydoc AppWindow::setName() */
        void setName(const char* value);

        /** \copydoc AppWindow::getSize() */
        void getSize(int* x, int* y) const;

        /** \copydoc AppWindow::getPosition() */
        void getPosition(int* left, int* top) const;
};

#endif // #ifndef _APPWINDOWSDL2_H_
