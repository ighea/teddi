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


#ifndef _FONTCORE_HPP
#define _FONTCORE_HPP

#include <iostream>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class FontCore
{
private:
	static FontCore *thisFontCore_;
	bool isTTFInitDone_;
	
	FontCore();
	
	std::vector<TTF_Font *> FontList;

public:
	static FontCore * GetInstance(void);
	~FontCore();
	void Init(void);
	TTF_Font * LoadFont(const char file[], int fontsize);
	
};

#endif
