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

#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include "Sync.hpp"
#include "Texture.hpp"

class Sprite
{
private:
	bool FREEME_;
	bool DeleteAfterZeroAlpha_;
	
	float red_,blue_,green_;
	
	double x_;
	double y_;
	int h_;
	int w_;
	double scale_;
	float angle_;
	float alpha_;
	double frame_;
	double velocity_;
	double lifetime_;
	bool visible_;
	bool useColorKey_;
	std::vector <Texture *> TextureList;
	
	bool FadeAway_;

public:
	Sprite(Texture *texture, double lifetime = -1, double frameChangeSpeed = 3, bool visible = true, bool useColorKey = false, float alpha = 1);
	~Sprite();
	Sprite(const Sprite& sprite);

	void SetPosition(double x, double y);
	void SetPosition(double x, double y, float angle);
	void SetScale(double scale);
	void SetAngle(float angle);
	double GetX();
	double GetY();
	int GetHeight(void);
	int GetWidth(void);
	float GetAngle();
	double GetScale();
	void Draw();
	void Append(Texture *texture); //Adds another sprite for animation
	void Destroy();
	void SetVisibility(bool visibility);
	bool GetVisibility();
	void SetUseColorKey(bool useColorKey);
	void SetAlphaLevel(float alpha);
	float GetAlphaLevel(void);
	void SetAnimationSpeed(double frameChangeSpeed); //Can be zero or greater

	void SetFreeMe(void);
	bool GetFreeMe(void);
	
	void SetFadeAway(void);
	void SetFadeAwayOff(void);
	void SetRGBValues(float red, float green, float blue);
	
	void SetDeleteAfterZeroAlpha(void);

};

#include "GraphicCore.hpp"

#endif
