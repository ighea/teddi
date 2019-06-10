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

#ifndef _BULLET_HPP
#define _BULLET_HPP

#include <iostream>
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Object.hpp"
#include "math.hpp"
#include "Sound.hpp"
#include "LogicCore.hpp"

class Creature;

class Bullet: public Object 
{
private:
	int damage_;
	double velocity_;
	int	maxrange_;
	bool bMaxRange_;
	Sprite *anim_;
	Object *owner_;
	bool Destroyed_;
	
	int startx_;
	int starty_;
	
public:	

	Bullet(int x, int y, int startAngle, double startVelocity, Sprite *sprite_bullet, int damage, int maxrange, Object *owner, bool areadamage = false, Texture *tAreaDamage = NULL);
	~Bullet();
	void Update(void);

	Object * GetOwner(void);
	void SetOwner(Object * owner); 
	void Destroy(void);
	
	void MoveForward(void);
	void MoveForward(float amount);

	int GetDamage(void);
	bool GetIsDestroyed(void);
	void SetIsDestroyed(bool state);
};



#endif
