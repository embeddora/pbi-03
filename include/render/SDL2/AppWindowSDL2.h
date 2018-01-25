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

#ifndef _APPWINDOWSDL2_H_
#define _APPWINDOWSDL2_H_

#include <iostream>

#include <SDL2/SDL.h>

#include "render/AppWindow.h"


/**
 * Render a Window using SDL2 
 *
 * \author  Constantin Masson
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
