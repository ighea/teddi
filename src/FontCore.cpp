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

#include "FontCore.hpp"

FontCore *FontCore::thisFontCore_ = 0;


FontCore::FontCore()
{
	std::cout << "FontCore created.\n";
	isTTFInitDone_ = false;
}

FontCore * FontCore::GetInstance(void)
{
	if (thisFontCore_ == 0)
	{
		thisFontCore_ = new FontCore();	
	}	
	return thisFontCore_;	
}

FontCore::~FontCore()
{
	//TTF_CloseFont(font);
	
	if(TTF_WasInit())
	{
		
		for (int i = 0; i < FontList.size(); i++)
		{
			if (FontList.at(i))
			{
				TTF_CloseFont(FontList.at(i));	
			}	
		}
		FontList.clear();
		
		TTF_Quit();
	}
}

void FontCore::Init(void)
{
	std::cout << "Initializing FontCore..";
	if (!isTTFInitDone_)	
	{
		isTTFInitDone_ = true;
		if (TTF_Init() == -1)
		{
			std::cerr << "Something went wry wrong here!\n";
			exit(1);	
		}	
		std::cout << "OK!\n";
	}
	else
	{
		std::cerr << "Already initialized!\n";
	}
}	


TTF_Font * FontCore::LoadFont(const char file[], int fontsize)
{
	TTF_Font *font = 0;
	font = TTF_OpenFont(file, fontsize);
	if (font == NULL){
		printf("Error while loading font file: %s %s \n",file, TTF_GetError());
		// Handle the error here.
	}
	else
	{
		FontList.push_back(font);	
	}

	return font;	
}
