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


#include "Player.hpp"

void Player::Update(void)
{
	if (GetIsDead())
	{
		//DEAD!! ;D	
	}
	else 
	{
		if (GetHP() < 1)
		{
		
			SetIsDead(true);
			
		}
		
		Keyboard *keys = Keyboard::GetInstance();

		if (keys->GetIsDown(SDLK_UP))
		{	
			SetIsMovingForward(true);	
		}
		if (keys->GetIsDown(SDLK_DOWN))
		{
			SetIsMovingBackward(true);	
		}
		if (keys->GetIsDown(SDLK_LEFT))
		{
			SetIsTurningLeft(true);	
		}
		if (keys->GetIsDown(SDLK_RIGHT))
		{
			SetIsTurningRight(true);	
		}
		if (keys->GetIsDown(SDLK_LCTRL))
		{
			SetIsAttacking(true);
		}	
	
		if (keys->GetIsUp(SDLK_UP))
		{
			SetIsMovingForward(false);	
		}
		if (keys->GetIsUp(SDLK_DOWN))
		{
			SetIsMovingBackward(false);	
		}
		if (keys->GetIsUp(SDLK_LEFT))
		{
			SetIsTurningLeft(false);	
		}
		if (keys->GetIsUp(SDLK_RIGHT))
		{
			SetIsTurningRight(false);	
		}
		if (keys->GetIsUp(SDLK_LCTRL))
		{
			SetIsAttacking(false);
		}	

		if (GetIsMovingForward() && GetCanMove())
		{
			//	MoveForward();
		}
		if (GetIsMovingBackward() && GetCanMove())
		{
	//		MoveBackward();	
		}
		if (GetIsTurningLeft())
		{
			TurnLeft();
		}
		if (GetIsTurningRight())
		{
			TurnRight();
		}
		
		if (GetIsAttacking() == true)
		{
			if (GetWeapon()) 
			{
				GetWeapon()->Attack();	
			}
		}
		else if (GetWeapon()) 
		{
			GetWeapon()->Update();	
		}	

	
		if (GetIsMovingForward() || GetIsMovingBackward())
		{
			if (GetAnimation()) 
			{
				GetAnimation()->SetCurrentAnimation(moving);
				GetAnimation()->SetPosition((int)GetX(),(int)GetY(),(int)GetAngle());
			}
		}
		else
		{
			if (GetAnimation()) 
			{
				GetAnimation()->SetCurrentAnimation(idle);
				GetAnimation()->SetPosition((int)GetX(),(int)GetY(),(int)GetAngle());
			}
		}
		
	}
	
}


void Player::BringUp(void)
{
	Animation *tmp;
	Animation *animp = GetAnimation();
	tmp = new Animation(*animp);
	delete animp;
	animp = new Animation(*tmp);
	delete tmp;
}
