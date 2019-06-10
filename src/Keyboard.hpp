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

#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP

#include <iostream>
#include <SDL/SDL.h>

class Keyboard
{
private:
	int keys_[322];
	static Keyboard *thisKeyboard_; 
	Keyboard();
public:
	static Keyboard* GetInstance(void);
	~Keyboard();
	void SetKeyState(int key, bool pressed);
	bool GetIsDown(int key);
	bool GetIsUp(int key);
	
};


#endif
