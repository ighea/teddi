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

#include "Placeable.hpp"

Placeable::Placeable(float x, float y, float angle)
{
	SetX(x);
	SetY(y);
	SetAngle(angle);
	Destroyed_ = false;
	isGround_ = false;
	LogicCore::GetInstance()->AppendPlaceableToList(this);
}

Placeable::Placeable(const Placeable &placeable)
{
	isGround_ = placeable.isGround_;
		
	x_ = placeable.x_;	
	y_ = placeable.y_;	
	h_ = placeable.h_;	
	w_ = placeable.w_;	
	angle_ = placeable.angle_;	

	if (placeable.sprite_) 
	{
		sprite_ = new Sprite(*placeable.sprite_);
		sprite_->SetPosition(x_,y_,angle_);
	}
	else 
	{
		sprite_ = 0;	
	}

	Destroyed_ = false;
	
	LogicCore::GetInstance()->AppendPlaceableToList(this);

}

void Placeable::SetSprite(Sprite *sprite)
{
	sprite_ = sprite;
	sprite_->SetUseColorKey(true);	
	SetHeight(sprite->GetHeight());
	SetWidth(sprite_->GetWidth());
}

Sprite * Placeable::GetSprite(void)
{
	return sprite_;	
}

void Placeable::SetPosition(float x, float y)
{
	SetX(x);
	SetY(y);
	if (sprite_) sprite_->SetPosition(x,y);
	
}

void Placeable::SetPosition(float x, float y, float angle)
{
	SetX(x);
	SetY(y);
	SetAngle(angle);
	if (sprite_) sprite_->SetPosition(x,y,angle);
	
}

void Placeable::Update()
{
	//Doodi doo placeableh...
}

void Placeable::SetIsGround(bool state)
{
	isGround_ = state;	
}

bool Placeable::GetIsGround(void)
{
	return isGround_;	
}

void Placeable::SetIsDestroyed(bool state)
{
	Destroyed_ = state;
}

bool Placeable::GetIsDestroyed(void)
{
	return Destroyed_;	
}
