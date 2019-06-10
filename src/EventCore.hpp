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


#ifndef _EVENTCORE_HPP
#define _EVENTCORE_HPP

#include <iostream>
#include <vector>
#include "Sync.hpp"
#include "SDL/SDL.h"
#include "Object.hpp"
#include "Debug.hpp"
#include "Keyboard.hpp"

class EventCore
{
private:
	static EventCore * thisEventCore_;
	SDL_Event event_;
	bool isExitKeyPressed_;

protected:
	EventCore();
	
public:
	static EventCore *GetInstance(void);
	~EventCore();
	
	void Update(void);
	bool GetIsExitKeyPressed(void);	
	void SetIsExitKeyPressed(bool state);

	void WaitForKeyPress(void);
};


#endif
