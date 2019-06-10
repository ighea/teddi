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

#ifndef _MATH_HPP
#define _MATH_HPP

#include <iostream>
#include <math.h>
#include "SDL/SDL.h"
#include "Object.hpp"

int Random(int min, int max);

double DecToRad(double dec);

bool testCircleCollision(Object *s1, Object *s2, int fix=0);

double AngleTowards(int xfrom, int yfrom, int xto, int yto);

int GetDistance(int xf, int yf, int xt, int yt);

#endif
