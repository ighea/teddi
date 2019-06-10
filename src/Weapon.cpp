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

#include "Weapon.hpp"

Weapon::Weapon(int damage, int range, double firerate, int bulletVelocity, int angleoffset)
{
	angleoffset_ = angleoffset;
	weaponDamage_ = damage;
	weaponRange_ = range;
	weaponFireRate_ = firerate;	
	sound_weapon_ = 0;
	bulletVelocity_ = bulletVelocity;
	sprite_bullet_ = 0;
	sprite_weapon_ = 0;
	OwnerOfWeapon = 0;

	currentfireratecalculator_ = 10;
}

Weapon::Weapon(const Weapon &weapon)
{
	angleoffset_ = weapon.angleoffset_;
	weaponDamage_ = weapon.weaponDamage_;
	weaponRange_ = weapon.weaponRange_;
	weaponFireRate_ = weapon.weaponFireRate_;	
	sound_weapon_ = weapon.sound_weapon_;
	bulletVelocity_ = weapon.bulletVelocity_;

	if (weapon.sprite_bullet_)
	{
		sprite_bullet_ = new Sprite(*weapon.sprite_bullet_);
	}
	else
	{
		sprite_bullet_ = 0;	
	}

	if (weapon.sprite_weapon_)
	{
		sprite_weapon_ = new Sprite(*weapon.sprite_weapon_);
	}
	else
	{
		sprite_weapon_ = 0;	
	}
	
	OwnerOfWeapon = 0;

	currentfireratecalculator_ = 10;
}


Weapon::~Weapon()
{
//	OwnerOfWeapon = 0;
	
}

void Weapon::SetOwner(Creature *owner)
{
	if (OwnerOfWeapon == NULL || OwnerOfWeapon == 0)
	{	
		OwnerOfWeapon = owner;
	}
	else
	{
//		std::cerr << "Warning: Could not assign OwnerOfWeapon" << std::endl;	
	}
}

Creature * Weapon::GetOwner(void)
{
	return OwnerOfWeapon;
}

void Weapon::SetWeaponSprite(Sprite *sprite)
{
	sprite_weapon_ = sprite;
}

void Weapon::SetBulletSprite(Sprite *sprite)
{
	sprite_bullet_ = sprite;
}

void Weapon::Attack(void)
{
	currentfireratecalculator_ = currentfireratecalculator_ + Sync::GetInstance()->GetShift();

	if (currentfireratecalculator_ >= weaponFireRate_)
	{
		currentfireratecalculator_ = 0;

		if (GetOwner() != 0 && GetOwner() != NULL)
		{
		
			//Weapon sound
			if (sound_weapon_ != 0 && sound_weapon_ != NULL)
			{
				sound_weapon_->Play();
			}
		
			//Weapon effects
			if (sprite_weapon_ != 0 && sprite_weapon_ != NULL)
			{
					sprite_weapon_->SetVisibility(true);
//					sprite_weapon_->SetAngle(GetOwner()->GetAngle());
					sprite_weapon_->SetUseColorKey(true);
					sprite_weapon_->SetPosition(GetOwner()->GetX(), GetOwner()->GetY(), GetOwner()->GetAngle());
			}
		
			//Possible bullet effects and such
			Bullet *bullet = new Bullet((int)GetOwner()->GetX(), (int)GetOwner()->GetY(), (int)GetOwner()->GetAngle() + angleoffset_, bulletVelocity_
			, sprite_bullet_, weaponDamage_, weaponRange_, GetOwner(), false, NULL);
		}
		else
		{
			std::cout << "Owner of the weapon is not set!!\n";
		}
	
	}

}


void Weapon::SetWeaponSound(Sound *weaponsound)
{
	sound_weapon_ = weaponsound;	
}

void Weapon::Update(void)
{
	if (GetOwner())
	{
		if (GetOwner()->GetIsAttacking() == false && (sprite_weapon_))
		{
			sprite_weapon_->SetVisibility(false);	
		}
		UpdateWeaponSpritePosition((int)GetOwner()->GetX(),(int)GetOwner()->GetY(), (int)GetOwner()->GetAngle());
	}
}

void Weapon::UpdateWeaponSpritePosition(int x, int y, int angle)
{
	if (sprite_weapon_)
	{
		sprite_weapon_->SetPosition(x,y,angle);
	}	
}
