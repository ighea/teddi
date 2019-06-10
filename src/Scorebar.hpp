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

#ifndef _SCOREBAR_HPP
#define _SCOREBAR_HPP

#include <iostream>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Texture.hpp"
#include "Sprite.hpp"

class Scorebar
{
private:
	int valuetotrail_;
	int lastvalue_;
	int x_;
	int y_;
	int h_;
	int w_;
	char *text_;
	Sprite *thebar_;
	TTF_Font *font_;
	SDL_Color color_;
	Texture *texture_;
	bool TextInsteadOfImage_;
	
	std::vector <Sprite *> SList;
	bool Upwards_;
	bool FromLeftToRight_;

public:
	Scorebar(const char caption[],TTF_Font *font, int valuetotrail, SDL_Color color, int x, int y);
	Scorebar(Texture *texture, int valuetotrail, int x, int y, bool FromLeftToRight = false, bool Upwards = false);
	~Scorebar();
	void SetPosition(int x, int y);
	int GetWidth(void);
	int GetHeight(void);
	void Update(int value);
	
};


#endif
