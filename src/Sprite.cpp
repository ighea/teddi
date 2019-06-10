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

#include "Sprite.hpp"

Sprite::Sprite(Texture *texture, double lifetime, double frameChangeSpeed, bool visible, bool useColorKey, float alpha)
{
//	texture_ = 0;
	FREEME_ = false;
	FadeAway_ = false;
	DeleteAfterZeroAlpha_ = false;
	
	if (texture == 0 || texture == NULL)
	{
		std::cout << "WTF!? NULL or 0 pointer at Sprite's texture!\n";	
	}
	
	w_ = texture->GetW();
	h_ = texture->GetH();

	if (w_ < 0) w_ = 1;
	if (h_ < 0) h_ = 1;

	red_=1.0f;
	green_=1.0f;
	blue_=1.0f;

	x_ = 0;
	y_ = 0;
	scale_ = 1;
	angle_ = 0;
	frame_ = 0;

	alpha_ = alpha; //Alpha between 0 and 1
	velocity_ = frameChangeSpeed;
	lifetime_ = lifetime;
	visible_ = visible;
	useColorKey_ = useColorKey;
	
	TextureList.push_back(texture);
	
	//Add the Sprite to the end of SpriteList in GraphicCore
	GraphicCore::GetInstance()->AddSprite(this);
	
}

//Copy constructor
Sprite::Sprite(const Sprite& sprite)
{
	
	FREEME_ = false;
	FadeAway_ = sprite.FadeAway_;

	red_= sprite.red_;
	green_=sprite.green_;
	blue_=sprite.blue_;


	w_ = sprite.w_;
	h_ = sprite.h_;

	x_ = sprite.x_;
	y_ = sprite.y_;
	scale_ = sprite.scale_;
	angle_ = sprite.angle_;
	frame_ = sprite.frame_;

	alpha_ = sprite.alpha_; //Alpha between 0 and 1
	velocity_ = sprite.velocity_;
	lifetime_ = sprite.lifetime_;
	visible_ = sprite.visible_;
	useColorKey_ = sprite.useColorKey_;
	
	TextureList = sprite.TextureList;	
	//Add the Sprite to the end of SpriteList in GraphicCore
	GraphicCore::GetInstance()->AddSprite(this);
	
	DeleteAfterZeroAlpha_ = sprite.DeleteAfterZeroAlpha_;
 }
	

Sprite::~Sprite()
{

}

void Sprite::SetPosition(double x, double y)
{
	x_ = x;
	y_ = y;
}

void Sprite::SetPosition(double x, double y, float angle)
{
	x_ = x;
	y_ = y;
	angle_ = angle;
}


void Sprite::SetScale(double scale)
{
	scale_ = scale;
}

void Sprite::SetAngle(float angle)
{
	angle_ = angle;
}


double Sprite::GetX()
{
	return x_;
}

double Sprite::GetY()
{
	return y_;

}

float Sprite::GetAngle()
{
	return angle_;
}

double Sprite::GetScale()
{
	return scale_;
}

void Sprite::Draw()
{
	//About to be removed, not continueing
	if (GetFreeMe()) return;
	
	int sx = GraphicCore::GetInstance()->GetScreenX();
	int sy = GraphicCore::GetInstance()->GetScreenY();
	
	
	
	if (TextureList.size() == 0)
	{
		std::cout << "Sprite with empty TextureList!!!?!11\n";
		return;	
	}
	else if (x_ > sx + w_ || x_ < -w_ || y_ > sy + h_ || y_ < -h_ )
	{
		//Sprite is out of screen, we won't draw it.
		return;	
	}
	
	unsigned int i = 0;
	int w=0,h=0;

	double shift = Sync::GetInstance()->GetShift();

	frame_ = frame_ + velocity_ * shift;
	i = (int)frame_;

	if (i > TextureList.size() - 1) 
	{
		i = 0;
		frame_ = 0;
	}
	
	//SetFreeme(); after zero alpha:
	if (DeleteAfterZeroAlpha_ == true && alpha_ <= 0)
	{
		SetFreeMe();
	}

//	std::cout << "Frame: " << i << " " << frame_ << std::endl;

	//Check if Sprite is set as visible and has Textures to draw...
	if (visible_ == true && TextureList.at(i)->GetTexture() != 0 && TextureList.at(i)->GetTexture() != NULL)
	{

		//Fading the sprite away..
		if (FadeAway_)
		{
			alpha_ = alpha_ - 1*Sync::GetInstance()->GetShift();
/*			if (alpha_ <= 0.0) 
			{	
				SetFreeMe();	
			}
*/		}


//Store current matrix
	glPushMatrix();

		if (useColorKey_)
		{
			//Use blending
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(red_, green_, blue_,  alpha_);

		} else
		{
			//Disable blending for now
			glBlendFunc(GL_ONE,GL_ZERO);
		}

		if (TextureList.at(i)->GetTexture() == 0 || TextureList.at(i)->GetTexture() == NULL)
		{
			std::cerr << "WTF is this shit? Sprites texture is fucked UP! GRRR!\n";
			return;	
		}
		
		glBindTexture( GL_TEXTURE_2D, *TextureList.at(i)->GetTexture() );

		glTranslatef(x_, y_, 0);  
		glRotatef(-GetAngle(), 0, 0, 1);

		glBegin( GL_QUADS );

			w = (int)w_>>1 ;
			h = (int)h_>>1 ;

			glTexCoord2i( 1, 1 );
			glVertex2f(w*scale_,h*scale_);
			glTexCoord2i( 0, 1 );
			glVertex2f(-w*scale_,h*scale_);
			glTexCoord2i( 0, 0 );
			glVertex2f(-w*scale_,-h*scale_);
			glTexCoord2i( 1, 0 );
			glVertex2f(w*scale_,-h*scale_);

		glEnd();	
//Restore last matrix
	glPopMatrix();

}

	if (lifetime_ != -1)
	{
	lifetime_ = lifetime_ - shift;
	if (lifetime_ <= 0)
	{
		Destroy();
	}
	}
}


void Sprite::Append(Texture *texture)
{
	//Just add a new texture to the bottom of the TextureList
	if (texture != 0 && texture != NULL)
	{
		TextureList.push_back(texture);
	}
	else
	{
		std::cerr << "Invalid texture in Append to Sprite!\n";	
	}

}

void Sprite::Destroy()
{
	//Mark this sprite as to be removed
	SetFreeMe();
}

void Sprite::SetVisibility(bool visibility)
{
	visible_ = visibility;
}

bool Sprite::GetVisibility()
{
	return visible_;
}

void Sprite::SetUseColorKey(bool useColorKey)
{
	useColorKey_ = useColorKey;	
}

int Sprite::GetHeight(void)
{
		return h_;
}

int Sprite::GetWidth(void)
{
		return w_;	
}

void Sprite::SetAlphaLevel(float alpha)
{
	if (alpha < 0.0f) 
	{
		alpha_ = 0.0f;
	} else if (alpha > 1)
	{
		alpha_ = 1;
	} else
	{
		alpha_ = alpha;	
	}
}

float Sprite::GetAlphaLevel(void)
{
	return alpha_;	
}

void Sprite::SetAnimationSpeed(double frameChangeSpeed)
{
	if (frameChangeSpeed >= 0)
	{
		velocity_ = frameChangeSpeed;
	}

}

void Sprite::SetFreeMe(void)
{
	FREEME_ = true;	
}

bool Sprite::GetFreeMe(void)
{
	return FREEME_;	
}

void Sprite::SetRGBValues(float red, float green, float blue)
{
	red_ = red;
	blue_ = blue;
	green_ = green;	
}

void Sprite::SetFadeAway(void)
{
	FadeAway_ = true;	
}
void Sprite::SetFadeAwayOff(void)
{
	FadeAway_ = false;	
}

void Sprite::SetDeleteAfterZeroAlpha(void)
{
	DeleteAfterZeroAlpha_ = true;	
}
