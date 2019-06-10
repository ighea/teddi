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


#include "Object.hpp"

Object::Object(float x ,float  y , float z , float angle, float velocity , float height , float width)
{	
	x_ = x;
	y_ = y;
	z_ = z;
	h_ = height;
	w_ = width;
	angle_ = angle;
	velocity_ = velocity;
		
}

Object::~Object(void)
{
//	std::cout << "Object destructor.\n";
}

void Object::SetPosition(float x, float y, float angle)
{
	x_ = x;
	y_ = y;
	angle_ = angle;
}

void Object::SetPosition(float x, float y)
{
	x_ = x;
	y_ = y;
}


float Object::GetX(void)
{
	return x_;
}
float Object::GetY(void)
{
	return y_;
}
float Object::GetZ(void)
{
	return z_;
}
float Object::GetHeight(void)
{
	return h_;	
}
float Object::GetWidth(void)
{
	return w_;
}
float Object::GetVelocity()
{
	return velocity_;
}
float Object::GetAngle()
{
	return angle_;
}

void Object::SetAngle(float angle)
{
	if (angle < 0)
	{
		angle = 360 + angle;	
	}
	else if (angle > 360)
	{
		angle = angle - 360;	
	}
	angle_ = angle;	
}
void Object::SetHeight(float height)
{
	h_ = height;
}
void Object::SetWidth(float width)
{
	w_ = width;
}
void Object::SetVelocity(float value)
{
	velocity_ = value;
}
void Object::SetX(float x)
{
	x_ = x;	
}
void Object::SetY(float y)
{
	y_ = y;	
}
void Object::SetZ(float z)
{
	z_ = z;	
}
