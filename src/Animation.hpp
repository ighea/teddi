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
#ifndef _ANIMATION_HPP
#define _ANIMATION_HPP

#include <iostream>
#include "Sprite.hpp"

enum t_animation {idle, moving, attacking, hit};

class Animation
{
private:
	t_animation CurrentAnimation_;
	Sprite *Sprites_[4];

public:
	Animation(Sprite *s_idle = 0, Sprite *s_moving = 0, Sprite *s_attacking = 0, Sprite *s_hit = 0);
	Animation(const Animation &anim);
	~Animation();
	void SetPosition(int x, int y, int angle);
	Sprite *GetSprite(t_animation animation);
	t_animation GetCurrentAnimation(void);
	void SetCurrentAnimation(t_animation anim);
	void AssingAnimation(Sprite *sprite, t_animation anim);
};


#endif
