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

#ifndef _OBJECT_HPP
#define _OBJECT_HPP

#include <iostream>

class Object
{
protected:
	float x_;
	float y_;
	float z_;
	float h_;
	float w_;
	float angle_;
	float velocity_;
public:
	Object(float x = 0,float  y = 0, float z = 0, float angle = 0, float velocity = 0, float height = 0, float width = 0 );
	~Object();
	virtual void Update() = 0;

	void SetPosition(float x, float y, float angle);
	void SetPosition(float x, float y);

	void SetAngle(float angle);
	void SetHeight(float height);
	void SetWidth(float width);
	void SetVelocity(float value); 
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float GetX(void);
	float GetY(void);
	float GetAngle(void);
	float GetVelocity(void);
	float GetHeight(void);
	float GetWidth(void);
	float GetZ(void);

};

#endif
