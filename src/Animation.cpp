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

#include "Animation.hpp"

Animation::Animation(Sprite *s_idle, Sprite *s_moving , Sprite *s_attacking , Sprite *s_hit )
{
	CurrentAnimation_ = idle;	
	Sprites_[idle] = s_idle;
	Sprites_[moving] = s_moving;
	Sprites_[attacking] = s_attacking;
	Sprites_[hit] = s_hit;
	
}

Animation::Animation(const Animation &anim)
{
	CurrentAnimation_ = anim.CurrentAnimation_;	
/*	Sprites_[idle] = anim.Sprites_[idle];
	Sprites_[moving] = anim.Sprites_[moving];
	Sprites_[attacking] = anim.Sprites_[attacking];
	Sprites_[hit] = anim.Sprites_[hit];
*/
	if (anim.Sprites_[idle])
	{
		Sprites_[idle] = new Sprite(*anim.Sprites_[idle]);
	}
	else
	{
		Sprites_[idle] = 0;	
	}	
	if (anim.Sprites_[moving])
	{
		Sprites_[moving] = new Sprite(*anim.Sprites_[moving]);
	}
	else
	{
		Sprites_[moving] = 0;	
	}	
	if (anim.Sprites_[attacking])
	{
		Sprites_[attacking] = new Sprite(*anim.Sprites_[attacking]);
	}
	else
	{
		Sprites_[attacking] = 0;	
	}	
	if (anim.Sprites_[hit])
	{
		Sprites_[hit] = new Sprite(*anim.Sprites_[hit]);
	}
	else
	{
		Sprites_[hit] = 0;	
	}	


}

Animation::~Animation()
{
	if (Sprites_[idle]) Sprites_[idle]->SetFreeMe();
	if (Sprites_[moving]) Sprites_[moving]->SetFreeMe();
	if (Sprites_[attacking]) Sprites_[attacking]->SetFreeMe();
	if (Sprites_[hit]) Sprites_[hit]->SetFreeMe();
	
}

void Animation::SetPosition(int x, int y, int angle)
{
	for (int i = 0; i < 4;i++)
	{
		if (Sprites_[i] != 0) Sprites_[i]->SetPosition(x,y,angle);	
	}
}

Sprite * Animation::GetSprite(t_animation animation)
{
	return Sprites_[animation];	
}

t_animation Animation::GetCurrentAnimation(void)
{
	return CurrentAnimation_;	
}

void Animation::SetCurrentAnimation(t_animation anim)
{
	CurrentAnimation_ = anim;
	for (int i = 0; i < 4; i++)
	{
		if (Sprites_[i] != 0)
		{
			if (i == CurrentAnimation_)
			{
				Sprites_[i]->SetVisibility(true);
			}
			else
			{
				Sprites_[i]->SetVisibility(false);
			}	
		}	
	}	
}

void Animation::AssingAnimation(Sprite *sprite, t_animation anim)
{
	Sprites_[anim] = sprite;	
}
