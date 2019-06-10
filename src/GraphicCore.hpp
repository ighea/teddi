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

#ifndef _GRAPHICCORE_HPP
#define _GRAPHICCORE_HPP

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Texture.hpp"
#include "Sprite.hpp"

class GraphicCore
{
private:
	static GraphicCore *thisGraphicCore_;
	SDL_Surface *screen_;
	int screenX_;
	int screenY_;
	int screenBPP_;
	
	int CurrentLayer_;
	int LayersCount_;

	float CurrentFPS_;
	int LastFPS_;
	long LastFPSUpdateTime_;

	std::vector <Sprite *> * SpriteList;

protected:
	GraphicCore();

public:
	
	~GraphicCore();
	bool Init(const char *WindowCaption = "Funky game engine, not!", int screenX = 640, int screenY = 480, int screenBPP = 24, int ScreenLayersCount = 1);
	void Update();
	static GraphicCore *GetInstance();
	SDL_Surface *GetScreen();
	
	int GetScreenX(void);
	int GetScreenY(void);
	
	void ClearScreen(void);

	void RemoveAllSprites(void);
	void RemoveAllTexturesFromSprites(void);
	
	void SetCurrentLayer(int layer);
	int GetCurrentLayer(void);
	int GetLayerCount(void);
	void RemoveAllSpritesFromLayer(int layer);
	void AddSprite(Sprite *sprite);
	
	void FPScounter(void);

};

#endif
