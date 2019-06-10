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

#include "Scorebar.hpp"

Scorebar::Scorebar(Texture *texture, int valuetotrail, int x, int y, bool FromLeftToRight, bool Upwards)
{
	TextInsteadOfImage_ = false;
	x_ = x;
	y_ = y;
	texture_ = texture;
	w_ = texture_->GetW();
	h_ = texture_->GetH();
	SList.clear();
	FromLeftToRight_ = FromLeftToRight;
	Upwards_ = Upwards;
	valuetotrail_ = valuetotrail;
}

Scorebar::Scorebar(const char caption[],TTF_Font *font, int valuetotrail, SDL_Color color, int x, int y)
{
	TextInsteadOfImage_ = true;
	
	valuetotrail_ = valuetotrail;
	color_ = color;
	font_ = font;
	x_ = x;
	y_ = y;
	char *tmpchar = new char[strlen(caption) + 10];
	
	text_ = new char[strlen(caption)+1];
	
	
	strcpy(text_, caption);

	sprintf(tmpchar ,"%s%i", text_, valuetotrail_);
	texture_ = new Texture(font_, tmpchar, solid, color_);
	thebar_ = new Sprite(texture_);	
	
	w_ = texture_->GetW();
	h_ = texture_->GetH();

	lastvalue_ = valuetotrail_ - 1 ;
	
	delete tmpchar;
}

Scorebar::~Scorebar()
{
	if (text_) delete [] text_;
	if (texture_) delete texture_;
	if (thebar_) thebar_->SetFreeMe();	
	
}


void Scorebar::Update(int value)
{
		valuetotrail_ = value;

		if (valuetotrail_ != lastvalue_)
		{
			lastvalue_ = valuetotrail_;

			if (TextInsteadOfImage_)
			{
				char *tmpchar = new char[strlen(text_) + 10];
				sprintf(tmpchar ,"%s%i", text_, valuetotrail_);

				if (thebar_) 
				{
					thebar_->SetFreeMe();
					thebar_ = 0;
				}
				if (texture_) 
				{
					delete texture_;
					texture_ = 0;
				}
				
				texture_ = new Texture(font_, tmpchar, solid, color_);
			
				w_ = texture_->GetW();
				h_ = texture_->GetH();

				thebar_ = new Sprite(texture_);	
				thebar_->SetPosition(x_, y_);
				thebar_->SetUseColorKey(true);
				delete tmpchar;
				tmpchar = 0;
			}
			else
			{
				
				for (int i = 0;i < SList.size();i++)
				{
					if (SList.at(i)) 
					{
						SList.at(i)->SetFreeMe();
						SList.at(i) = 0;
					}
				}
				SList.clear();
				
				for (int i = 0; i < valuetotrail_; i++)
				{
					thebar_ = new Sprite(texture_);
					thebar_->SetUseColorKey(true);
					SList.push_back(thebar_);
				}
				SetPosition(x_,y_);				
			}
		}
	
}


void Scorebar::SetPosition(int x, int y)
{
	x_ = x;
	y_ = y;
	if (TextInsteadOfImage_) 
	{
		thebar_->SetPosition(x,y);
	}
	else
	{
		for (int i = 0;i < SList.size();i++)
		{
			if (SList.at(i)) 
			{
				if (!FromLeftToRight_)
				{
					SList.at(i)->SetPosition(x_ - i * w_, y_);
				}
				else if (FromLeftToRight_)
				{
					SList.at(i)->SetPosition(x_ + i * w_, y_);
				}
				if (Upwards_)
				{
					SList.at(i)->SetPosition(x_, y_ - i * h_);
				}
				
			}
		}

	}
}

int Scorebar::GetWidth(void)
{
	return w_;	
}

int Scorebar::GetHeight(void)
{
	return h_;	
}
