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
#include "Bullet.hpp"

Bullet::~Bullet()
{
	if (anim_ != 0 && anim_ != NULL) 
	{
		anim_->SetFreeMe();
	}
	
//	std::cout << "Bullet destructor\n";	
}

Bullet::Bullet(int x, int y, int startAngle, double startVelocity, Sprite *sprite_bullet, int damage, int maxrange, Object *owner, bool areadamage, Texture *tAreaDamage): Object(x,y,startAngle,startVelocity)
{
	owner_ = 0;
	anim_ = 0;
	velocity_ = startVelocity;
	owner_ = owner;
	damage_ = damage;
	maxrange_ = maxrange;
	Destroyed_ = false;

	SetPosition(x,y);
	startx_ = x;
	starty_ = y;
	
	bMaxRange_ = false;

	SetAngle(startAngle);

	if (owner_ != 0 && owner_ != NULL) MoveForward(owner_->GetHeight()/2);

	if (sprite_bullet)
	{
		anim_ = new Sprite(*sprite_bullet);
		anim_->SetPosition(GetX(), GetY());
		anim_->SetUseColorKey(true);
		anim_->SetAngle(startAngle);
		SetWidth(anim_->GetWidth());
		SetHeight(anim_->GetHeight());
	}
	else
	{
		SetHeight(1);
		SetWidth(1);
	}
	
	LogicCore::GetInstance()->AppendBulletToList(this);
}


void Bullet::Update(void)
{
		
	if (anim_ != 0 && anim_ != NULL)
	{
		anim_->SetPosition(GetX(), GetY());
	}

	if (GetDistance(startx_,starty_,(int)GetX(),(int)GetY()) >= maxrange_)
	{
		bMaxRange_ = true;
		Destroy();	
	}
	else
	if (GetX() > GraphicCore::GetInstance()->GetScreenX() || GetX() < 0 || GetY() < 0 || GraphicCore::GetInstance()->GetScreenY() < GetY() )
	{
		//Bullet is out of screen: destroy it.
		Destroy();	
	}
	else
	{
		if (bMaxRange_)
		{
			//Max range of bullet reached
		} 
		else 
		{
			MoveForward();
		}
	}

}


Object * Bullet::GetOwner(void)
{
	return owner_;	
}

void Bullet::SetOwner(Object * owner)
{
	owner_ = owner;	
}

void Bullet::Destroy(void)
{
	if (anim_) anim_->SetVisibility(false);
	Destroyed_ = true;
	
}

void Bullet::MoveForward(void)
{
	SetX(GetX() + Sync::GetInstance()->GetShift() * velocity_ * cos(DecToRad(GetAngle())) );	
	SetY(GetY() - Sync::GetInstance()->GetShift() * velocity_ * sin(DecToRad(GetAngle())) );	
}

void Bullet::MoveForward(float amount)
{
	SetX(GetX() + amount * cos(DecToRad(GetAngle())) );	
	SetY(GetY() - amount * sin(DecToRad(GetAngle())) );	
}

int Bullet::GetDamage(void)
{
	return damage_;	
}

bool Bullet::GetIsDestroyed(void)
{
	return Destroyed_;	
}
void Bullet::SetIsDestroyed(bool state)
{
	Destroyed_ = state;	
}
