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

#include "LogicCore.hpp"


LogicCore * LogicCore::thisLogicCore_ = 0;

LogicCore::LogicCore()
{
	std::cout << "LogiCore created!\n";	
}

LogicCore * LogicCore::GetInstance(void)
{
	if (thisLogicCore_ == 0)
	{
		thisLogicCore_ = new LogicCore();
	}
	return thisLogicCore_;	
}

LogicCore::~LogicCore()
{
	
}

void LogicCore::AppendCreatureToList(Creature *creature)
{
	ListOfCreatures.push_back(creature);	
}

void LogicCore::AppendPlaceableToList(Placeable *placeable)
{
	ListOfPlaceables.push_back(placeable);	
}

void LogicCore::AppendBulletToList(Bullet *bullet)
{
	ListOfBullets.push_back(bullet);	
}


void LogicCore::Update(void)
{
	Dummy *dummy = new Dummy();
	
	//Update all creatures and do collision checks
	for (int i = 0;i < ListOfCreatures.size(); i++)
	{
		if (ListOfCreatures.at(i)) 
		{
			ListOfCreatures.at(i)->SetCanMove(true);
			dummy->SetPosition(ListOfCreatures.at(i)->GetX(), ListOfCreatures.at(i)->GetY(),ListOfCreatures.at(i)->GetAngle());
			dummy->SetVelocity(ListOfCreatures.at(i)->GetVelocity());
			dummy->SetHeight(ListOfCreatures.at(i)->GetHeight());
			dummy->SetWidth(ListOfCreatures.at(i)->GetWidth());			
			
			if (ListOfCreatures.at(i)->GetIsMovingForward())
			{
				dummy->MoveForward();	
			}
			if (ListOfCreatures.at(i)->GetIsMovingBackward())
			{
				dummy->MoveBackward();	
			}
			//Test if ListOfCreatures.at(i) collides with another Creature
			for (int j=0;j<ListOfCreatures.size();j++)
			{
				if (ListOfCreatures.at(j) != ListOfCreatures.at(i))
				{
					//Creature is dead: skip
					if (ListOfCreatures.at(j)->GetIsDead()) continue;

					if (testCircleCollision(dummy, ListOfCreatures.at(j),3))
					{
						ListOfCreatures.at(i)->SetCanMove(false);
							
					}
				}
			}
			
			//Or with a Placeable
			for (int k = 0;k < ListOfPlaceables.size(); k++)
			{
				if (ListOfPlaceables.at(k)->GetIsGround() == false)
				{
					if (testCircleCollision(dummy, ListOfPlaceables.at(k),3))
					{
						ListOfCreatures.at(i)->SetCanMove(false);
					}
				}
			}	

		}
	}	
	
	for (int i = 0; i < ListOfBullets.size();i++)
	{
		if (ListOfBullets.at(i))
		{
			//Bullet is Destroyed: skip
			if (ListOfBullets.at(i)->GetIsDestroyed()) continue;
			
			//Creatures hit
			for (int j = 0; j < ListOfCreatures.size(); j++)
			{
				if (ListOfCreatures.at(j))
				{
					if ( ListOfCreatures.at(j) != ListOfBullets.at(i)->GetOwner() && !ListOfCreatures.at(j)->GetIsDead())
					{
						if (testCircleCollision(ListOfBullets.at(i), ListOfCreatures.at(j)))
						{
							ListOfCreatures.at(j)->IsDamaged((int)ListOfBullets.at(i)->GetDamage(), (int)ListOfBullets.at(i)->GetX(), (int)ListOfBullets.at(i)->GetY());
							ListOfBullets.at(i)->Destroy();
							continue;
						}	
					}
				}
			}

			//Collision with placeable
			for (int j = 0; j < ListOfPlaceables.size(); j++)
			{
				if (ListOfPlaceables.at(j))
				{
//					if ( !ListOfPlaceables.at(j)->GetIsGround() && !ListOfPlaceables.at(j)->GetIsDestroyed())
					{
						if (!ListOfPlaceables.at(j)->GetIsGround() && testCircleCollision(ListOfBullets.at(i), ListOfPlaceables.at(j)))
						{
//							ListOfPlaceables.at(j)->IsDamaged(ListOfBullets.at(i)->GetDamage());
							ListOfBullets.at(i)->Destroy();
							continue;
						}	
					}
				}
			}

		}	
	}
	
	HandleObjects();
	
	delete dummy;
	
	
	//Do updates for objects:
	
	for (int i = 0; i < ListOfPlaceables.size();i++)
	{	
		if (ListOfPlaceables.at(i))
		{
			ListOfPlaceables.at(i)->Update();		
		}
	}

	for (int i = 0; i < ListOfCreatures.size();i++)
	{	
		if (ListOfCreatures.at(i))
		{
			ListOfCreatures.at(i)->Update();		
		}
	}

	for (int i = 0; i < ListOfBullets.size();i++)
	{	
		if (ListOfBullets.at(i))
		{
			ListOfBullets.at(i)->Update();		
		}
	}

}


void LogicCore::UpdateBulletLocations(float xc, float yc)
{
	for (int i = 0; i < ListOfBullets.size();i++)
	{
		if (ListOfBullets.at(i))
		{
			ListOfBullets.at(i)->SetPosition(ListOfBullets.at(i)->GetX() + xc, ListOfBullets.at(i)->GetY() + yc);	
		}	
	}
		
}

void LogicCore::HandleObjects(void)
{
	int i = 0;

//	std::cout << "Creature deletion:\n";
	for (i = 0; i < ListOfCreatures.size(); i++)
	{
		if (ListOfCreatures.at(i))
		{
//			std::cout << "checking..\n";
			if (ListOfCreatures.at(i)->GetIsDestroyed())
			{
//				std::cout << "Destroyed creature: deleting..";
				Map::GetInstance()->RemoveCreatureFromMap(ListOfCreatures.at(i));	
				delete ListOfCreatures.at(i);
				ListOfCreatures.at(i) = 0;
				ListOfCreatures.erase(ListOfCreatures.begin() + i);
//				std::cout << "OK!\n";
//				return;
			}
		}
		else 
		{
//			std::cout << "Empty ListOfCreatures pointer!?\n";
			ListOfCreatures.erase(ListOfCreatures.begin() + i);
//			return;
		}	
	}

//	std::cout << "Placeable deletion:\n";
	for (i = 0; i < ListOfPlaceables.size(); i++)
	{
		if (ListOfPlaceables.at(i))
		{
//			std::cout << "checking..\n";
			if (ListOfPlaceables.at(i)->GetIsDestroyed())
			{
//				std::cout << "Destroyed creature: deleting..";
				Map::GetInstance()->RemovePlaceableFromMap(ListOfPlaceables.at(i));	
				delete ListOfPlaceables.at(i);
				ListOfPlaceables.at(i) = 0;
				ListOfPlaceables.erase(ListOfPlaceables.begin() + i);
//				std::cout << "OK!\n";
//				return;
			}
		}
		else 
		{
//			std::cout << "Empty ListOfPlaceables pointer!?\n";
			ListOfPlaceables.erase(ListOfPlaceables.begin() + i);
//			return;
		}	
	}

//	std::cout << "Bullet deletion:\n";
	for (i = 0; i < ListOfBullets.size(); i++)
	{
		if (ListOfBullets.at(i))
		{
//			std::cout << "checking..\n";
			if (ListOfBullets.at(i)->GetIsDestroyed())
			{
//				std::cout << "Destroyed creature: deleting..";
				delete ListOfBullets.at(i);
				ListOfBullets.at(i) = 0;
				ListOfBullets.erase(ListOfBullets.begin() + i);
//				std::cout << "OK!\n";
				return;
			}
		}
		else 
		{
//			std::cout << "Empty ListOfPlaceables pointer!?\n";
			ListOfBullets.erase(ListOfBullets.begin() + i);
			return;
		}	
	}
	std::cout << "P:" << ListOfPlaceables.size() << " C:" << ListOfCreatures.size() << "\n";
}
