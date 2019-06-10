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


#include "Map.hpp"

Map *Map::thisMap_ = 0;

Map * Map::GetInstance(void)
{
	
	if (!thisMap_ || thisMap_ == 0)
	{
		thisMap_ = new Map();	
	}
	
	return thisMap_;
}

Map::Map()
{
	
}

void Map::Init(int sizeX, int sizeY, const char terrain_texture_file[], Creature *objecttotrace)
{
	MapEnded_ = false;
	sizex_ = sizeX;
	sizey_ = sizeY;
	player_ = objecttotrace;

	finish_ = 0;
	finishp_ = 0;
	
	SetTerrain(terrain_texture_file);
	
	endx_= sizeX/2;
	endy_= sizeY/2;
	startx_= sizeX/2;
	starty_= sizeY/2+1;
	
	//Map virtual left top corner
	distance_from_left_ = 0;
	distance_from_top_ = 0;
}

Map::~Map()
{
	
}

void Map::GenerateMap(void)
{
	MapEnded_ = false;
	std::cout << "Map generator begin...\n";
	int counter = 0;
	
	bool table[sizex_][sizey_];
	bool wg_table[sizex_][sizey_]; //Holds the passage ways, can be reused for creatures and items
	
	std::cout << "Map size [" << sizex_<< ","<<sizey_<<"]\n";
	
	//Set whole table[] and wg_table[] as false
	for (int y=0; y < sizey_; y++)
	{
		for (int x=0; x < sizex_;x++)
		{
			table[x][y] = false;
			wg_table[x][y] = false;
		}
	}


	//Generate background
	if (background_ != 0 && background_ != NULL)
	{
		Sprite *background_sprite;
		for (int x=0; x < (GraphicCore::GetInstance()->GetScreenX()/background_->GetW())+1; x++)
		{
			for (int y=0; y < (GraphicCore::GetInstance()->GetScreenY()/background_->GetH())+1; y++)
			{
				background_sprite = new Sprite(background_);
				background_sprite->SetPosition(background_sprite->GetWidth()/2+x*background_sprite->GetWidth(),background_sprite->GetHeight()/2+y*background_sprite->GetHeight());
			}	
		}
	}
	
	
	std::cout << "Generating terraint..\n";
	
	//Generate terrain
	Sprite *terrain_sprite;
	for (int x=0; x < sizex_; x++)
	{
		for (int y=0; y < sizey_; y++)
		{
			terrain_sprite = new Sprite(terrain_);
			terrain_sprite->SetPosition(terrain_sprite->GetWidth()/2+x*terrain_sprite->GetWidth(),terrain_sprite->GetHeight()/2+y*terrain_sprite->GetHeight());
			GroundSpriteList.push_back(terrain_sprite);
		}	
	}


	std::cout << "Terrain done.\n";
	std::cout << "Creating objects:\n";
	
	
	//Object creation:
	int placex=0, placey=0;
	Creature *tmpcreature;
	Placeable *tmpplaceable;
	int k=0;
	
	//Set start & end points as reserved
	table[(startx_-1)][(starty_-1)] = true;
	table[(endx_-1)][(endy_-1)] = true;
	
	
//Generate free passages	
	int wg_crosspoints = Random(1,(int)sqrt(sqrt(sizex_*sizey_)))/2 + 2;
	
	struct point
	{
		int x;
		int y;
	};
	point wg_map[wg_crosspoints];
	for (int i = 1 ; i < wg_crosspoints - 1; i++)
	{
		wg_map[i].x = Random(0,sizex_-1);
		wg_map[i].y = Random(0,sizey_-1);
		table[wg_map[i].x][wg_map[i].y] = true;
	}
	wg_map[0].x = startx_-1;
	wg_map[0].y = starty_-1;
	
	wg_map[wg_crosspoints-1].x = endx_-1;
	wg_map[wg_crosspoints-1].y = endy_-1;
	
	int wgx;
	int wgy;
	
	for (int i = 0;i < wg_crosspoints - 1; i++)
	{
		wgx = wg_map[i].x;
		wgy = wg_map[i].y;
		table[wgx][wgy] = true;
		if (i != 0 && i == wg_crosspoints -1) wg_table[wgx][wgy] = true;
		while (wgx != wg_map[i+1].x || wgy != wg_map[i+1].y )
		{
			table[wgx][wgy] = true;
			if (i != 0 && i == wg_crosspoints -1) wg_table[wgx][wgy] = true;
			if (wgx > wg_map[i+1].x)
			{
				wgx--;
			}
			else if (wgx < wg_map[i+1].x)
			{
				wgx++;
			}
			table[wgx][wgy] = true;
			if (i != 0 && i == wg_crosspoints -1) wg_table[wgx][wgy] = true;
			if (wgy > wg_map[i+1].y)
			{
				wgy--;
			}
			else if (wgy < wg_map[i+1].y)
			{
				wgy++;
			}
			table[wgx][wgy] = true;
			if (i != 0 && i == wg_crosspoints -1) wg_table[wgx][wgy] = true;
		}	
	}
	
		
	//Push objects to the area:

	std::cout << "Creating placeables..";
	for (int i=0; i < PWClist.size(); i++)
	{
		placex = Random(1,sizex_);
		placey = Random(1,sizey_);

		if (table[(placex-1)][(placey-1)] == false || table[(placex-1)][(placey-1)] == true && wg_table[(placex-1)][(placey-1)] == true)
		{
			table[(placex-1)][(placey-1)] = true;
			tmpplaceable = new Placeable(*PWClist.at(i).object);
			tmpplaceable->SetPosition(placex*32-16, placey*32-16,Random(1,359));
			PlaceableList.push_back(tmpplaceable);
			counter++;
			std::cout << ".";
		k=0;
		}
		else
		{
			//Fail, lets try again
			i--;
			k++;
		}
		if (k> (sizex_ * sizey_) ) break;
	}
	k=0;
	std::cout << "OK!\n";


	if (finish_ != 0) 
	{
		finish_ = new Creature(*finish_);
		finish_->SetPosition(endx_* 32 - 16,endy_*32 - 16);
		CreatureList.push_back(finish_);
	}
	else if (finishp_ != 0)
	{
		finishp_ = new Placeable(*finishp_);
		finishp_->SetPosition(endx_* 32 - 16,endy_*32 - 16);
		PlaceableList.push_back(finishp_);
		
	}


		
	std::cout << "Creating creatures..";
	for (int i=0; i < CWClist.size(); i++)
	{
		placex = Random(1,sizex_);
		placey = Random(1,sizey_);

		if (table[(placex-1)][(placey-1)] == false)
		{
			table[(placex-1)][(placey-1)] = true;
			tmpcreature = new Creature(*CWClist.at(i).object);
			tmpcreature->SetPosition(placex*32-16, placey*32-16, Random(0,359));
			CreatureList.push_back(tmpcreature);
			counter++;
			std::cout << ".";
		k=0;
		}
		else
		{
			//Fail, lets try again
			i--;
			k++;
		}
		if (k> (sizex_ * sizey_) ) break;
	}
	std::cout << "OK!\n";
	
	//Setting player to the startpoint if possible
	if (player_) player_->SetPosition(startx_*32-16,starty_*32-16);
	
	std::cout << "Created " << counter << " of " << CWClist.size() + PWClist.size() << "\nDone.\n";

	std::cout << "Map finished.\n";

	//Reassingn all objects so that the player_ is on the center of the screen
	if (player_)
	{
		std::cout << "Repositioning object locations";
		int x = int(player_->GetX());
		int y = int(player_->GetY());
		int sx=GraphicCore::GetInstance()->GetScreenX();
		int sy=GraphicCore::GetInstance()->GetScreenY();

		player_->SetPosition(sx/2,sy/2);
	
		float xc =  player_->GetX() -x;
		float yc = player_->GetY() -y;

		distance_from_left_ = startx_*32 - 16;
		distance_from_top_ = starty_*32 - 16;
		
		
		for (int i=0;i<CreatureList.size();i++)
		{
			if (CreatureList.at(i)) 
			{
				
				CreatureList.at(i)->SetPosition(CreatureList.at(i)->GetX()+xc, CreatureList.at(i)->GetY()+yc);
				std::cout << ".";
			}
		}

		for (int i=0;i<PlaceableList.size();i++)
		{
			if (PlaceableList.at(i)) 
			{
				
				PlaceableList.at(i)->SetPosition(PlaceableList.at(i)->GetX()+xc, PlaceableList.at(i)->GetY()+yc);
				std::cout << ".";
			}
		}


		for (int i=0;i<GroundSpriteList.size();i++)
		{
			if (GroundSpriteList.at(i)) 
			{
				GroundSpriteList.at(i)->SetPosition(GroundSpriteList.at(i)->GetX()+xc, GroundSpriteList.at(i)->GetY()+yc);
				std::cout << ".";
			}
		}
		
		std::cout << "Ok\n";
	}


	Update();
//	delete &table;
}

void Map::AppendCreature(Creature *type, int count)
{
	CreatureWithCount CWCmember;
	
	for (int i= 0; i < count;i++)
	{
		CWCmember.object = type;
		CWCmember.count = count;
		CWClist.push_back(CWCmember);	
	}
}

void Map::AppendPlaceable(Placeable *type, int count)
{
	PlaceableWithCount PWCmember;
	
	for (int i= 0; i < count;i++)
	{
		PWCmember.object = type;
		PWCmember.count = count;
		PWClist.push_back(PWCmember);	
	}
}


void Map::SetStartPoint(int x, int y)
{
	startx_ = x;
	starty_ = y;
}

void Map::SetEndPoint(int x, int y)
{
	endy_ = y;
	endx_ = x;
}

void Map::SetSize(int sizeX, int sizeY)
{
	sizex_ = sizeX;
	sizey_ = sizeY;	
}

void Map::SetTerrain(const char terrain_texture_file[])
{
	terrain_ = new Texture(terrain_texture_file);	
}
	
void Map::SetPlayer(Creature *object)
{
	player_ = object;
}

void Map::ClearObjectLists(void)
{
	PWClist.clear();
	CWClist.clear();
	PlaceableList.clear();
	CreatureList.clear();
	GroundSpriteList.clear();
}

void Map::SetEndCreature(Creature *finish)
{
	finish_ = finish;
}

void Map::SetEndPlaceable(Placeable *finishp)
{
	finishp_ = finishp;
}

int Map::GetSizeX(void)
{
	return sizex_;
}

int Map::GetSizeY(void)
{
	return sizey_;
}

void Map::ClearMap(void)
{
	//Clear all objects stored in MAp's vectors
	finish_ = 0;
	finishp_ = 0;
	for (int i = 0; i < CreatureList.size(); i++)
	{
		if (CreatureList.at(i))
		{
			CreatureList.at(i)->SetHP(0);
			CreatureList.at(i)->SetIsDestroyed(true);
			CreatureList.at(i)->SetIsDead(true);
			CreatureList.erase(CreatureList.begin() + i);
			std::cout << "Creature removed from map!\n";
		}	
	}
	for (int i = 0; i < PlaceableList.size(); i++)
	{
		if (PlaceableList.at(i))
		{
			PlaceableList.at(i)->SetIsDestroyed(true);
			if (PlaceableList.at(i)->GetSprite()) PlaceableList.at(i)->GetSprite()->SetFreeMe();
			PlaceableList.erase(PlaceableList.begin() + i);
			std::cout << "Placeable removed from map!\n";	
		}	
	}
	for (int i = 0; i < GroundSpriteList.size(); i++)
	{
		if (GroundSpriteList.at(i))
		{
			GroundSpriteList.at(i)->SetFreeMe();	
			GroundSpriteList.erase(GroundSpriteList.begin() + i);
		}	
	}
	LogicCore::GetInstance()->HandleObjects();
	ClearObjectLists();
	GroundSpriteList.clear();
	PlaceableList.clear();
	CreatureList.clear();
	CWClist.clear();
	PWClist.clear();
	
	
}


void Map::Update()
{
	
	if (player_)
	{
		if (finish_ != 0)
		{
			if (finish_->GetHP() < 1)
			{
				SetMapEnded(true);	
				std::cout << "Map boss slayed!\n";
			}
		}
		if (finishp_ != 0)
		{
			if (testCircleCollision(player_, finishp_,4) == true)
			{
				SetMapEnded(true);	
				std::cout << "Map waypoint reached!\n";
			}
		
		}
				
		float xc=0,yc=0;

		float x=(int)player_->GetX();
		float y=(int)player_->GetY();
		int sx=GraphicCore::GetInstance()->GetScreenX();
		int sy=GraphicCore::GetInstance()->GetScreenY();

		Dummy *dummy = new Dummy();
		dummy->SetPosition(x, y, player_->GetAngle());
		dummy->SetVelocity(player_->GetVelocity());

		if (player_->GetIsMovingForward() && player_->GetCanMove())				
		{
			dummy->MoveBackward();	
		}			
		if (player_->GetIsMovingBackward() && player_->GetCanMove())				
		{
			dummy->MoveForward();	
		}			
		xc = dummy->GetX() - x;
		yc = dummy->GetY() - y;
				
		//Prevent player from leaving the area
		if (distance_from_left_ < 16)
		{
			xc--;			
		}
		if (distance_from_left_ > SizeXInPixels() - 16)
		{
			xc++;
		}
		if (distance_from_top_ < 16)
		{
			yc--;
		}
		if (distance_from_top_ > SizeYInPixels() - 16)
		{
			yc++;
		}

		//Maps top left corner location:
		distance_from_left_ = distance_from_left_ - xc;
		distance_from_top_ = distance_from_top_ - yc;

		//Placeable pos updates
		for (int i=0;i<PlaceableList.size();i++)
		{
			if (PlaceableList.at(i)) 
			{
				PlaceableList.at(i)->SetPosition(PlaceableList.at(i)->GetX()+xc, PlaceableList.at(i)->GetY()+yc);
			}
		}

		//Ground Sprite pos updates
		for (int i=0;i<GroundSpriteList.size();i++)
		{
			if (GroundSpriteList.at(i)) 
			{
				GroundSpriteList.at(i)->SetPosition(GroundSpriteList.at(i)->GetX()+xc, GroundSpriteList.at(i)->GetY()+yc);
			}
		}
					
		//Creature pos updates
		for (int i=0; i < CreatureList.size();i++)
		{
			if (CreatureList.at(i)) 
			{
				CreatureList.at(i)->SetPosition(CreatureList.at(i)->GetX()+xc, CreatureList.at(i)->GetY()+yc);
				//Prevent creature from leaving the area from right
				if (distance_from_left_ + (CreatureList.at(i)->GetX() - player_->GetX()) >  SizeXInPixels() - CreatureList.at(i)->GetWidth()/2 )
				{	
					CreatureList.at(i)->SetX(CreatureList.at(i)->GetX() - 1);
				}
				//Prevent creature from leaving the area from left
				if (distance_from_left_ + (CreatureList.at(i)->GetX() - player_->GetX()) < + CreatureList.at(i)->GetWidth()/2 )
				{	
					CreatureList.at(i)->SetX(CreatureList.at(i)->GetX() + 1);
				}
				//Prevent creature from leaving the area from bottom
				if (distance_from_top_ + (CreatureList.at(i)->GetY() - player_->GetY()) >  SizeYInPixels() - CreatureList.at(i)->GetHeight()/2 )
				{	
					CreatureList.at(i)->SetY(CreatureList.at(i)->GetY() - 1);
				}
				//Prevent creature from leaving the area from top
				if (distance_from_top_ + (CreatureList.at(i)->GetY() - player_->GetY()) < + CreatureList.at(i)->GetHeight()/2 )
				{	
					CreatureList.at(i)->SetY(CreatureList.at(i)->GetY() + 1);
				}
			}
		}
		
		//Update Bullet locations in LogicCore...
		LogicCore::GetInstance()->UpdateBulletLocations(xc, yc);

		delete dummy;	
	}
}


void Map::SetBackground(Texture *background)
{
	background_ = background;
	
}

void Map::PushCreatureToMap(Creature *creature)
{
	CreatureList.push_back(creature);	
}

void Map::PushSpriteToMap(Sprite *sprite)
{
	GroundSpriteList.push_back(sprite);	
}

int Map::SizeXInPixels(void)
{
	return (sizex_*32);
}

int Map::SizeYInPixels(void)
{
	return (sizey_*32);
}

void Map::RemoveCreatureFromMap(Creature *creature)
{
	for (int i = 0; i < CreatureList.size(); i++)
	{
		if (CreatureList.at(i) == creature)
		{
			CreatureList.erase(CreatureList.begin() + i);
			std::cout << "Creature removed from map!\n";
			return;	
		}	
	}
	
}

void Map::RemovePlaceableFromMap(Placeable *placeable)
{
	for (int i = 0; i < PlaceableList.size(); i++)
	{
		if (PlaceableList.at(i) == placeable)
		{
			PlaceableList.erase(PlaceableList.begin() + i);
			std::cout << "Placeable removed from map!\n";	
			return;
		}	
	}
	
}

void Map::SetMapEnded(bool state)
{
	MapEnded_ = state;	
}

bool Map::GetMapEnded(void)
{
	return MapEnded_;	
}
