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

#ifndef _WEAPON_HPP
#define _WEAPON_HPP

#include <iostream>
#include "SDL/SDL.h"
#include "Sync.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Object.hpp"
#include "Creature.hpp"
#include "Bullet.hpp"
#include "Sound.hpp"

class Creature;

class Weapon
{
private:
	Creature *OwnerOfWeapon;
	int weaponRange_;
	int weaponDamage_;
	int bulletVelocity_;
	double weaponFireRate_;
	double currentfireratecalculator_;
	Sprite *sprite_weapon_;
	Sprite *sprite_bullet_;
	Sound *sound_weapon_;
	int angleoffset_;

	void UpdateWeaponSpritePosition(int x, int y, int angle);
public:
	Weapon(const Weapon &weapon);
	Weapon(int damage = 1, int range = 100, double firerate = 5.0, int bulletvelocity=100, int angleOffset = 0);
	~Weapon();
	void SetOwner(Creature *owner);
	Creature * GetOwner(void);
	void Attack(void);
	void SetWeaponSprite(Sprite *sprite);
	void SetBulletSprite(Sprite *sprite);
	void SetWeaponSound(Sound *sound);
	void Update(void);
};

#endif
