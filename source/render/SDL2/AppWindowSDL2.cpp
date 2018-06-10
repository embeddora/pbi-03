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

#include "render/SDL2/AppWindowSDL2.h"


//------------------------------------------------------------------------------
// Constructors - Destructor
//------------------------------------------------------------------------------
AppWindowSDL2::AppWindowSDL2() : AppWindow()
{
	this->sdl_window    = NULL;

	this->sdl_renderer  = NULL;

	this->sdl_texture   = NULL;
}


//------------------------------------------------------------------------------
// General functions
//------------------------------------------------------------------------------

void AppWindowSDL2::initialize(const char* name, const int w, const int h)
{
    return this->initialize(name, w, h, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
}

// TODO To update: At the moment, flags is hard coded (To SDL_WINDOW_HIDDEN)
void AppWindowSDL2::initialize(const char* title, const int w, const int h, const int l, const int t)
{
	// Load sdl_window
	this->sdl_window = SDL_CreateWindow(title, l, t, w, h, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

	if(this->sdl_window == NULL)
	{
		std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;

		return;
	}

	// Load sdl_renderer
	this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, 0);

	if(this->sdl_renderer == NULL)
	{
		std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;

		return;
	}

	// Load texture
	this->sdl_texture = SDL_CreateTexture( this->sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	if(this->sdl_texture == NULL)
	{
		std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;

		return;
	}
}

void AppWindowSDL2::show()
{
	SDL_ShowWindow(this->sdl_window);
}

void AppWindowSDL2::hide()
{
	SDL_HideWindow(this->sdl_window);
}

void AppWindowSDL2::destroy()
{
	SDL_DestroyTexture(this->sdl_texture);

	SDL_DestroyRenderer(this->sdl_renderer);

	SDL_DestroyWindow(this->sdl_window);

	this->sdl_texture   = NULL;

	this->sdl_renderer  = NULL;

	this->sdl_window    = NULL;
}

void AppWindowSDL2::maximize()
{
    SDL_MaximizeWindow(this->sdl_window);
}

void AppWindowSDL2::minimize()
{
    SDL_MinimizeWindow(this->sdl_window);
}


//------------------------------------------------------------------------------
// Getter / Setters / Data
//------------------------------------------------------------------------------
const char* AppWindowSDL2::getName() const
{
    return SDL_GetWindowTitle(this->sdl_window);
}

void AppWindowSDL2::setName(const char* value)
{
    SDL_SetWindowTitle(this->sdl_window, value);
}

void AppWindowSDL2::getSize(int* x, int* y) const
{
    SDL_GetWindowSize(sdl_window, x, y);
}

void AppWindowSDL2::getPosition(int* left, int* top) const
{
    SDL_GetWindowPosition(sdl_window, left, top);
}
