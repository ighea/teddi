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

#ifndef _PLACEABLE_HPP
#define _PLACEABLE_HPP

#include <iostream>
#include <SDL/SDL.h>
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Object.hpp"
#include "LogicCore.hpp"

class Placeable: public Object
{
private:
	bool isGround_;
	Sprite * sprite_;
	bool Destroyed_;
public:
	Placeable(float x = 0, float y = 0, float angle = 0);
	Placeable(const Placeable &placeable);
	void SetSprite(Sprite *sprite);
	Sprite *GetSprite(void);
	void SetPosition(float x, float y);

	void SetPosition(float x, float y, float angle_);
	void Update();

	void SetIsGround(bool state);
	bool GetIsGround(void);

	void SetIsDestroyed(bool state);
	bool GetIsDestroyed(void);
	
};

#endif
