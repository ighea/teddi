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

#include "Sync.hpp"

Sync * Sync::thisSync_ = 0;

Sync::Sync() 
{
	thisSync_ = 0;
	atv = SDL_GetTicks();
	sync_ = 0;
	max_sync_ = 1000;
}

double Sync::GetShift()
{
	return sync_;
}

Sync::~Sync()
{

}

void Sync::Update()
{
	long int time;
	long int tv;

	tv = SDL_GetTicks();
        time = (tv - atv);
	if (time < 0) 
	{
		time = 0;
	}
	if (time > max_sync_)
	{
		time = max_sync_;
	}
	

    atv = SDL_GetTicks();
        
	sync_ = (time/1000.0);
}

Sync * Sync::GetInstance()
{
	if (thisSync_ == 0 || thisSync_ == NULL)
	{
		thisSync_ = new Sync();
	}
	return thisSync_;
}


void Sync::SetMaxSyncTime(int value_in_ms)
{
		max_sync_ = value_in_ms;
}
