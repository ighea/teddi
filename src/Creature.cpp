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

#include "Creature.hpp"


void Creature::SetIsDead(bool state)
{
	dead_ = state;
}

bool Creature::GetIsDead()
{
	return dead_;
}

Creature::Creature(int x, int y, int startAngle, double startVelocity, int hp, int maxhp, int isDead, bool isAI): Object(x,y, startAngle, startVelocity)
{
	hp_ = hp;
	enemy_creature_ = 0;
	maxhp_ = maxhp;
	dead_ = isDead;
	animation_ = new Animation();
	weapon_ = 0;
	ai_ = isAI;
	Destroyed_ = false;
	
	sound_washit_ = 0;
	
	
	SetPosition(x,y, startAngle);
	
	SetHeight(1);
	SetWidth(1);
	
	blood_texture_ = 0;
	sound_washit_ = 0;
	sprite_blood_ = 0;
	
	isAggressive_ = false;
	turning_speed_ = 180;
	velocity_ = startVelocity;
	
	isMovingBackward_ = false;
	isMovingForward_ = false;
	isTurningLeft_ = false;
	isTurningRight_ = false;
	isAttacking_ = false;
	SetCanMove(true);
	animation_ = 0;
	
	LogicCore::GetInstance()->AppendCreatureToList(this);
}

Creature::Creature(const Creature& creature)
{
	
	isMovingForward_ = creature.isMovingForward_;
	isMovingBackward_ = creature.isMovingBackward_;
	isTurningLeft_ = creature.isTurningLeft_;
	isTurningRight_ = creature.isTurningRight_;
	isAttacking_ = creature.isAttacking_;

	x_ = creature.x_;
	y_ = creature.y_;
	h_ = creature.h_;
	w_ = creature.w_;
	angle_ = creature.angle_;
	velocity_ = creature.velocity_;
	turning_speed_ = creature.turning_speed_;
	SetCanMove(true);
		

//Creat
	ai_ = creature.ai_;
	hp_ = creature.hp_;
	maxhp_ = creature.maxhp_;
	dead_ = false;//creature.dead_;
	Destroyed_ = false;
	enemy_creature_ = creature.enemy_creature_;

	if (creature.weapon_)
	{
		weapon_ = new Weapon(*(creature.weapon_));
		weapon_->SetOwner(this);
	}
	else weapon_ = 0;
	
	isAggressive_ = creature.isAggressive_;
	
	
	if (creature.blood_texture_) blood_texture_ = creature.blood_texture_;
	if (creature.sound_washit_) sound_washit_ = creature.sound_washit_;

	if (creature.animation_)
	{
		animation_ = new Animation(*creature.animation_);
		animation_->SetPosition((int)x_,(int)y_,(int)angle_);
	}

	if (creature.sprite_blood_)
	{
		sprite_blood_ = new Sprite(*creature.sprite_blood_);	
	}

	LogicCore::GetInstance()->AppendCreatureToList(this);
}


Creature::~Creature()
{
	if (animation_) delete animation_;
	if (weapon_) delete weapon_;
	if (sprite_blood_) sprite_blood_->SetFreeMe();
}


void Creature::Update()
{

	int sx = GraphicCore::GetInstance()->GetScreenX();
	int sy = GraphicCore::GetInstance()->GetScreenY();	

	//if creature is out from screen area we won't do a thing and save some CPU time
	if (GetX() + GetWidth() < 0 || GetX() - GetWidth() > sx || GetY() + GetHeight() < 0 || GetY() - GetHeight() > sy)
	{
		return;
	}
		
	//Are we dead yet?
	if (GetIsDead() == true)
	{
		//Uber dieying effects! ;D
		GetAnimation()->GetSprite(GetAnimation()->GetCurrentAnimation())->SetFadeAway();
		if (GetAnimation()->GetSprite(GetAnimation()->GetCurrentAnimation())->GetAlphaLevel() <= 0.0)
		{
			//Creature is totaly unvisible: Mark as Destroyed
			SetIsDestroyed(true);	
		}
	}
	else
	{
	//Still kicking, hu?

		//Lets be sure
		if (hp_ <= 0)
		{
			SetIsAIEnabled(false);
			HaltAllMovement();
			SetIsDead(true);
		}

		//Are we an intelligent life form?	
		if (GetIsAIEnabled() == true)
		{
			DoAIUpdate();
		}

		//Do the weapon usage-thingies
		if (GetIsAttacking() == true)
		{
			if (GetWeapon()) 
			{
				GetWeapon()->Attack();
				GetWeapon()->Update();	
			}
		}
		else if (GetWeapon()) 
		{
			GetWeapon()->Update();	
		}	


		//Turnings
		if (GetIsTurningLeft()) 
		{
			TurnLeft();
		}
	//	else
		if (GetIsTurningRight())
		{
			TurnRight();
		}

	
		if (GetIsMovingForward() && GetCanMove())
		{
			MoveForward();
		}
		if (GetIsMovingBackward() && GetCanMove())
		{
			MoveBackward();
		}

	}
	
	//Animation position updates
	if (animation_)
	{
		if (GetIsMovingBackward() || GetIsMovingForward())
		{
			animation_->SetCurrentAnimation(moving);	
			animation_->SetPosition((int)GetX(), (int)GetY(), (int)GetAngle());
		}
		else
		{
			animation_->SetCurrentAnimation(idle);	
			animation_->SetPosition((int)GetX(), (int)GetY(), (int)GetAngle());
		}
	}
	
}

void Creature::HaltAllMovement(void)
{
	SetIsTurningLeft(false);
	SetIsTurningRight(false);
	SetIsMovingBackward(false);
	SetIsMovingForward(false);
	SetIsAttacking(false);
	if (animation_) animation_->SetCurrentAnimation(idle);
}

void Creature::DoAIUpdate()
{
	
	
	if (GetIsAggressive())
	{
		int distance_from_enemy = GetDistance((int)GetX(),(int)GetY(),(int)enemy_creature_->GetX(),(int)enemy_creature_->GetY());
		if (distance_from_enemy < 100)
		{	
			HaltAllMovement();
//			SetAngle(AngleTowards((int)GetX(),(int)GetY(),(int)enemy_creature_->GetX(),(int)enemy_creature_->GetY()));	
			float at = AngleTowards((int)GetX(),(int)GetY(),(int)enemy_creature_->GetX(),(int)enemy_creature_->GetY());	
			float ac = at - GetAngle();
/*			
			if (at > GetAngle() )
			{
			
				SetIsTurningLeft(true);
			}
			else if (at < GetAngle())
			{
				SetIsTurningRight(true);	
			}
*/
			if (1 > ac > -1)
			{
				if (ac < 0 && ac > -180)
			{
				SetIsTurningRight(true);
			}
			else if (ac < -180)
			{
				SetIsTurningLeft(true);
			} else if (ac > 0 && ac < 180)
			{
				SetIsTurningLeft(true);	
			}
			else if (ac > 180)
			{
				SetIsTurningRight(true);	
			}
			}
						
			if (distance_from_enemy > (GetWidth() + GetHeight())/2 ) 
			{
				SetIsMovingForward(true);
			}
			
			if (distance_from_enemy < ((GetWidth() + GetHeight())/2)*2 )
			{
				if (weapon_ != 0 && weapon_ != NULL) weapon_->SetOwner(this);
				SetIsAttacking(true);	
			}
			
			return;
		}	
	}


	int j = Random(1,100);
	switch (j)
	{
		case 1:
			SetIsMovingForward(true);
		break;
		case 2:
			SetIsMovingForward(false);
		break;
		case 3:
			SetIsTurningLeft(true);
		break;
		case 4:
			SetIsTurningLeft(false);
		break;
		case 5:
			SetIsTurningRight(true);
		break;
		case 6:
			SetIsTurningRight(false);
		break;
		case 7:
			SetIsMovingForward(true);
		break;
		case 8:
			SetIsMovingForward(true);
		break;
		default:
		break;
	};
}

bool Creature::GetIsAIEnabled(void)
{
	return ai_;	
}

void Creature::SetIsAIEnabled(bool state)
{
	ai_ = state;	
}



/*void Creature::IsDamaged(int amount, int x, int y)
{
	decreaseHP(amount);	

	//Play the "got hit" sound
	if (washit_sound_ != 0 && washit_sound_ != NULL && !getIsDead())
	{
		washit_sound_->Play();	
	}
	//Put some blood
	if (blood_texture_ != 0 && blood_texture_ != NULL && !getIsDead())
	{
		if (x==-1) x=(int)GetX();
		if (y==-1) y=(int)GetY();

		Sprite *sprite = new Sprite(blood_texture_,1);
		sprite->SetUseColorKey(true);
		sprite->setPosition(x,y);
		sprite->setAngle(Random(0,359));
		sprite->SetFadeAway();
		Map::GetInstance()->PushSpriteToMap(sprite);
	}

}
	*/
int Creature::GetHP(void)
{
	return hp_;	
}

void Creature::SetHP(int hp)
{
	hp_ = hp;	
}

void Creature::SetCanMove(bool state)
{
	CanMove_ = state;	
}
bool Creature::GetCanMove(void)
{
	return CanMove_;
}
	
bool Creature::GetIsMovingForward(void)
{
	return isMovingForward_;	
}
bool Creature::GetIsMovingBackward(void)
{
	return isMovingBackward_;	
}
bool Creature::GetIsTurningLeft(void)
{
	return isTurningLeft_;	
}
bool Creature::GetIsTurningRight(void)
{
	return isTurningRight_;	
}
bool Creature::GetIsAttacking(void)
{
	return isAttacking_;	
}

void Creature::SetIsMovingForward(bool state)
{
	isMovingForward_ = state;	
}
void Creature::SetIsMovingBackward(bool state)
{
	isMovingBackward_ = state;	
}
void Creature::SetIsTurningLeft(bool state)
{
	isTurningLeft_ = state;	
}
void Creature::SetIsTurningRight(bool state)
{
	isTurningRight_ = state;	
}
void Creature::SetIsAttacking(bool state)
{
	isAttacking_ = state;	
}


void Creature::MoveForward(void)
{
	SetX(GetX() + Sync::GetInstance()->GetShift() * velocity_ * cos(DecToRad(GetAngle())) );	
	SetY(GetY() - Sync::GetInstance()->GetShift() * velocity_ * sin(DecToRad(GetAngle())) );	
}

void Creature::MoveBackward(void)
{
	SetX(GetX() - Sync::GetInstance()->GetShift() * velocity_ * cos(DecToRad(GetAngle())) );	
	SetY(GetY() + Sync::GetInstance()->GetShift() * velocity_ * sin(DecToRad(GetAngle())) );	
}

void Creature::TurnLeft(void)
{
	SetAngle(GetAngle() + Sync::GetInstance()->GetShift() * turning_speed_);	
}

void Creature::TurnRight(void)
{
	SetAngle(GetAngle() - Sync::GetInstance()->GetShift() * turning_speed_);	
}

void Creature::SetIsAggressive(bool state)
{
	isAggressive_ = state;	
}

bool Creature::GetIsAggressive(void)
{
	return isAggressive_;
}


Animation * Creature::GetAnimation(void)
{
	return animation_;	
}

void Creature::SetAnimation(Animation *anim)
{
	animation_ = anim;
	
	if (animation_)
	{
		if (animation_->GetSprite(idle))
		{
			SetHeight(animation_->GetSprite(idle)->GetHeight());
			SetWidth(animation_->GetSprite(idle)->GetWidth());
		}	
		else if (animation_->GetSprite(moving))
		{
			SetHeight(animation_->GetSprite(moving)->GetHeight());
			SetWidth(animation_->GetSprite(moving)->GetWidth());
		}	
	}	
}

Weapon * Creature::GetWeapon(void)
{
	return weapon_;	
}

void Creature::SetWeapon(Weapon *weapon)
{
	weapon_ = weapon;
	if (weapon_) weapon_->SetOwner(this);	
}

void Creature::SetTurningSpeed(int value)
{
	turning_speed_ = value;
	
}
int Creature::GetTurningSpeed(void)
{
	return (int)turning_speed_;	
}

void Creature::IsDamaged(int amount, int x, int y)
{
	if (x == -1 && y == -1)
	{
		x= (int)GetX();
		y =(int)GetY();	
	}
	hp_ = hp_ - amount;
	if (sound_washit_)
	{
		sound_washit_->Play();	
	}
	if (sprite_blood_)
	{
		Sprite *sprite = new Sprite(*sprite_blood_);
//		Map::GetInstance()->PushSpriteToMap(sprite);
		sprite->SetPosition(x + Random(-2,2), y+Random(-2,2), Random(0,359));
		sprite->SetFadeAway();
		sprite->SetUseColorKey(true);
		sprite->SetDeleteAfterZeroAlpha();
			
	}
	//Damage animation comes here! ;P
}

bool Creature::GetIsDestroyed(void)
{
	return Destroyed_;	
}

void Creature::SetIsDestroyed(bool state)
{
	Destroyed_ = state;	
}

void Creature::SetDamagedSound(Sound *sound)
{
	sound_washit_ = sound;	
}

void Creature::SetEnemy(Creature *enemy)
{
	enemy_creature_ = enemy;	
}

void Creature::SetBloodSprite(Sprite *sprite)
{
	sprite_blood_ = sprite;	
}
