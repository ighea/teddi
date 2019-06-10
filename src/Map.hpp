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

#ifndef _MAP_HPP
#define _MAP_HPP

#include <iostream>
#include <vector>
#include "SDL/SDL.h"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "GraphicCore.hpp"
#include "Object.hpp"
#include "Dummy.hpp"
#include "Placeable.hpp"
#include "Creature.hpp"
#include "LogicCore.hpp"

class LogicCore;
class Creature;
class Placeable;

struct CreatureWithCount
{
	Creature *object;
	int count;
};

struct PlaceableWithCount
{
	Placeable *object;
	int count;
};


class Map
{
private:
	bool MapEnded_;
	
	int startx_;
	int starty_;
	int endx_;
	int endy_;
	int sizex_;
	int sizey_;
		
	Creature *player_;
	Creature *finish_;
	Placeable *finishp_;
	Texture *terrain_;
	Texture *background_;

	std::vector <CreatureWithCount> CWClist;
	std::vector <PlaceableWithCount> PWClist;
	std::vector <Creature *> CreatureList;
	std::vector <Placeable *> PlaceableList;
	std::vector <Sprite *> GroundSpriteList;
	
	float distance_from_left_;
	float distance_from_top_;
	
	static Map *thisMap_;
	
	Map();
	int SizeXInPixels(void);
	int SizeYInPixels(void);
public:
	void Init(int sizeX = 20, int sizeY = 15, const char terrain_texture_file[]=0, Creature *objecttotrace = 0);
	~Map();
	
	static Map *GetInstance(void);

	void Update(void);

	void GenerateMap(void);

	void AppendCreature(Creature *type, int count);
	void AppendPlaceable(Placeable *type, int count);

	void SetStartPoint(int x, int y);
	void SetEndPoint(int x, int y);
	void SetEndCreature(Creature *finish);
	void SetEndPlaceable(Placeable *finishp);

	void SetSize(int sizeX, int sizeY);
	void SetTerrain(const char terrain_texture_file[]);
	
	
	void SetPlayer(Creature *object);
	
	void SetBackground(Texture *background);
	
	void ClearObjectLists(void);
	
	int GetSizeX(void);
	int GetSizeY(void);
	
	void ClearMap(void);
	
	void PushCreatureToMap(Creature *creature);
	void PushSpriteToMap(Sprite *sprite);
	
	void RemoveCreatureFromMap(Creature *creature);
	void RemovePlaceableFromMap(Placeable *palceable);
	
	
	void SetMapEnded(bool state);
	bool GetMapEnded(void);
};


#endif
