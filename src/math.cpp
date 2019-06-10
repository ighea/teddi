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

#include "math.hpp"

int Random(int min, int max)
{
	static bool Rseed = false;
	if (!Rseed)
	{
		Rseed = true;
		srand(SDL_GetTicks());	
	}
	
	int j = 0;	
	j = min + (int)((float)max * (rand() / (RAND_MAX + 1.0)));	
	return j;
}

double DecToRad(double dec)
{
	return (dec*(3.1416/180.0));
}

/**
    * Tests collision between bounding circles of two sprites. These 
    * circles are calculated (or, to be more exact, approximated)
    * on the fly, and for the moment their sizes cannot be changed.
    * This algorithm allows an error of 1 pixel. This cannot be changed,
    * either.
    * @param s1 Sprite to test
    * @param s2 Sprite to test
    * @return Wether sprite bounding circles are in contact with each other
    
**/

bool testCircleCollision(Object *rect0, Object *rect1, int fix) 
{
	int r0 = ((int)rect0->GetWidth()-fix + (int)rect0->GetHeight()-fix) >> 2; 
	int r1 = ((int)rect1->GetWidth()-fix + (int)rect1->GetHeight()-fix) >> 2;
	int dx = (int)rect1->GetX() - (int)rect0->GetX(); 
	int dy = (int)rect1->GetY() - (int)rect0->GetY();
	int dcentre_sq = (dy * dy) + (dx * dx); 
	int r_sum_sq = r0 + r1; r_sum_sq *= r_sum_sq;

	return (dcentre_sq - r_sum_sq <= 0); 
}

//Returns angle in degree towards point (x,y)
double AngleTowards(int xfrom, int yfrom, int xto, int yto)
{
	double angle = 0;
    double x = xto - xfrom;
    double y = yto - yfrom;
    
    //becouse divided by zero is no good :,<
    if (x==0) x=1;
    angle = atan( y / x ) * (180.0/3.14);
        
    if (x>0) angle = -angle;
    if (x<0) angle = -angle + 180;

    return angle;	
}

int GetDistance(int xf, int yf, int xt, int yt)
{
	int xs = xt - xf;
	int ys = yt - yf;
	int result = (int)sqrt(pow(xs,2) + pow(ys,2));
	return result;
}
