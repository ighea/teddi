/*
	Teddi the Bear: Quest of Red Ribbon
	Created by Mika 'ighea' Hynnä 
	Copyright 2007, Mika Hynnä
	http://mika.wippiesblog.com igheax@gmail.com
	
	
	* This file is part of Teddi the Bear: Quest of Red Ribbon.

    Teddi the Bear: Quest of Red Ribbon is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Teddi the Bear: Quest of Red Ribbon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	Read COPYING for more information.

*/

#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_ttf.h"


enum textquality {solid, shaded, blended};

class Texture
{
private:
	GLuint *texture_;
	int w_;
	int h_;
	void CreateTexture(SDL_Surface *tempTexture);
public:
	Texture(const char bmp_file[], int colorkeyR = 255, int colorkeyG = 255, int colorkeyB = 255);
	Texture(TTF_Font *font, const char text[], textquality quality ,SDL_Color color, int colorkeyR = 255, int colorkeyG = 255, int colorkeyB = 255);
	~Texture();
	GLuint *GetTexture();
	int GetH();
	int GetW();
};

#endif
