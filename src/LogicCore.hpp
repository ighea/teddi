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


#ifndef _LOGICCORE_HPP
#define _LOGICCORE_HPP

#include <iostream>
#include <vector>
#include "math.hpp"
#include "Object.hpp"
#include "Creature.hpp"
#include "Placeable.hpp"
#include "Bullet.hpp"
#include "Map.hpp"

class Creature;
class Placeable;
class Bullet;

class LogicCore
{
private:
	static LogicCore * thisLogicCore_;
	LogicCore();
	std::vector <Placeable *> ListOfPlaceables;
	std::vector <Creature *> ListOfCreatures;
	std::vector <Bullet *> ListOfBullets;


public:
	static LogicCore * GetInstance(void);
	~LogicCore();
	
	void Update(void);
	
	void AppendCreatureToList(Creature *creature);
	void AppendPlaceableToList(Placeable *placeable);
	void AppendBulletToList(Bullet *bullet);
	
	void UpdateBulletLocations(float xchange, float ychange);
	void HandleObjects(void);
};

#endif
