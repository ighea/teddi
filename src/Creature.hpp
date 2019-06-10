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

#ifndef _CREATURE_HPP
#define _CREATURE_HPP

#include <iostream>
#include <SDL/SDL.h>
#include <math.h>
#include "math.hpp"
#include "Sync.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Object.hpp"
#include "Weapon.hpp"
#include "Bullet.hpp"
#include "Debug.hpp"
#include "Animation.hpp"
#include "Dummy.hpp"
#include "LogicCore.hpp"

class Weapon;

class Creature: public Object
{
private:
	bool ai_;
	bool Destroyed_;
	int hp_;
	int maxhp_;
	bool dead_;
	Weapon *weapon_;	
	float turning_speed_;
	Sprite *sprite_blood_;

	Animation *animation_;

	Texture *blood_texture_;
	Sound *sound_washit_;
	
	Creature *enemy_creature_;
	
	bool isAggressive_;
	bool isMovingForward_, isMovingBackward_, isTurningLeft_, isTurningRight_, isAttacking_;
	bool CanMove_;
	

	void DoAIUpdate();
	
public:
	Creature(int x = 0, int y = 0, int startAngle = 0, double startVelocity = 0.0, int hp = 1, int maxhp = 1, int isDead = false, bool isAI = true);
	~Creature();

	Creature(const Creature& creature);

	void HaltAllMovement(void);

	void SetTurningSpeed(int value);
	int GetTurningSpeed(void);

	void SetIsDead(bool state);
	bool GetIsDead();

	void SetIsAIEnabled(bool state);
	bool GetIsAIEnabled(void);

	virtual void Update(void);
	
	Weapon * GetWeapon(void);
	void SetWeapon(Weapon *weapon);
	void RemoveWeapon(void);
	
	int GetHP(void);
	void SetHP(int hp);
	
	void SetCanMove(bool state);
	bool GetCanMove(void);
	
	bool GetIsMovingForward(void);
	bool GetIsMovingBackward(void);
	bool GetIsTurningLeft(void);
	bool GetIsTurningRight(void);
	bool GetIsAttacking(void);

	void SetIsMovingForward(bool state);
	void SetIsMovingBackward(bool state);
	void SetIsTurningLeft(bool state);
	void SetIsTurningRight(bool state);
	void SetIsAttacking(bool state);
	
	
	void MoveForward(void);
	void MoveBackward(void);
	void TurnLeft(void);
	void TurnRight(void);
	
	void SetIsAggressive(bool state);
	bool GetIsAggressive(void);
	
	void SetAnimation(Animation *anim);
	Animation * GetAnimation(void);
	
	
	void IsDamaged(int amount = 1, int x = -1, int y = -1);
	
	void SetIsDestroyed(bool state);
	bool GetIsDestroyed(void);
	
	void SetDamagedSound(Sound *sound);
	
	void SetEnemy(Creature *enemy);
	void SetBloodSprite(Sprite *sprite);
};

#endif
