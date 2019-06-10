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


#include "Keyboard.hpp"

Keyboard * Keyboard::thisKeyboard_ = 0;

Keyboard * Keyboard::GetInstance(void)
{
	if (thisKeyboard_ == 0)
	{
		thisKeyboard_ = new Keyboard();
	}
	return thisKeyboard_;
}

Keyboard::Keyboard()
{
	for (int i = 0; i < 322;i++)
	{
		keys_[i] = false;	
	}	
}

Keyboard::~Keyboard()
{
	
}

void Keyboard::SetKeyState(int key, bool pressed)
{
	keys_[key] = pressed;
}

bool Keyboard::GetIsDown(int key)
{
	return keys_[key];
}

bool Keyboard::GetIsUp(int key)
{
	if (keys_[key])
	{
		return false;		
	}
	else 
	{
		return true;	
	}
}
