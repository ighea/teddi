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


#include "GraphicCore.hpp"

GraphicCore * GraphicCore::thisGraphicCore_ = 0;

GraphicCore::GraphicCore()
{
	//Do nothing
	std::cout << "GraphicCore created!\n";
	CurrentLayer_ = 0;
	CurrentFPS_ = 0;
	LastFPSUpdateTime_ = 0;
}

GraphicCore::~GraphicCore()
{
	std::cout << "Freeing GraphicCore...\n";
	//Show cursor
	SDL_ShowCursor(1);
	
//	RemoveAllTexturesFromSprites();
	RemoveAllSprites();
	std::cout << "All Sprites destroyed.\n";
	
	delete [] SpriteList;
	
	SDL_Quit();

	std::cout << "Done.\n";
}

bool GraphicCore::Init(const char *WindowCaption, int screenX, int screenY, int screenBPP, int ScreenLayers)
{
	std::cout << "Initializing graphic core..";
	
	SpriteList = new std::vector <Sprite *> [ScreenLayers];
	CurrentLayer_ = 0;
	LayersCount_ = ScreenLayers;
	
	screenX_ = screenX;
	screenY_ = screenY;
	screenBPP_ = screenBPP;

	if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 )
	{
		std::cout << "GraphicCore Init failed" << SDL_GetError()<<"\n\n Exiting...\n";
		exit(1);
		return false;
	}

	SDL_WM_SetCaption(WindowCaption, NULL);

	//Always try to execute SDL_Quit() at exit.
	atexit(SDL_Quit);

	//set 8 bits for each color channel for OpenGL
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

/*
	screen_ = SDL_SetVideoMode(screenX_, screenY_, screenBPP_, SDL_HWSURFACE | SDL_DOUBLEBUF  );
	if(screen_ == NULL)
	{
		return false;
	}
*/
	
	//For OpenGL-init
	if (NULL == (screen_ = SDL_SetVideoMode(screenX_, screenY_, 0, SDL_OPENGL)))
	{
	    printf("Can't set OpenGL mode: %s\n", SDL_GetError());
	    SDL_Quit();
	    exit(1);
	}

	glEnable( GL_TEXTURE_2D ); 

	glViewport(0, 0,         // coordinates of the
                                 // lower left hand corner
                                 // of the window which we
                                 // will change in the
                                 // glOrtho() call.
             screen_->w,         // Set the logical width
             screen_->h);        // and height of the
                                 // window to match the
                                 // actual width and
                                 // height as measured in
                                 // pixels.

//	glMatrixMode( GL_PROJECTION );
//	glLoadIdentity();

// Set the coordinate system for the window moving (0,0)
// to the upper left hand corner of the window.
	glOrtho(0.0,                   // left edge is zero
        (GLdouble)screen_->w,   // right edge is width
        (GLdouble)screen_->h,   // bottom edge is height
        0.0,                   // top edge is zero
        0.0, 1.0);             // near and far clipping
                                 // planes.

//	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	// Set the clear color to black.
	glClearColor(0.0, 0.0, 0.0, 0.0);

//Enabling blending
	glEnable (GL_BLEND); 


	//Fill the screen with black color
//	SDL_FillRect(screen_, NULL, SDL_MapRGB(screen_->format, 0x00, 0x00, 0x00));

	//Hide cursor
	SDL_ShowCursor(0);

	std::cout << "OK!" << std::endl;
	return true;
}

void GraphicCore::Update()
{
	int i = 0;

	//Fill the screen with black color/clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Draw all sprites to the screen
	for (i = 0; i < SpriteList[CurrentLayer_].size(); i++)
	{
		if (SpriteList[CurrentLayer_].at(i) != 0 && SpriteList[CurrentLayer_].at(i) != NULL && SpriteList[CurrentLayer_].at(i))
		{
			if (SpriteList[CurrentLayer_].at(i)->GetFreeMe())
			{
				//Free Object from memory
				delete SpriteList[CurrentLayer_].at(i);
				SpriteList[CurrentLayer_].at(i) = 0;
				
				//Remove from the ObjectList

				SpriteList[CurrentLayer_].erase(SpriteList[CurrentLayer_].begin() + i);
				//break;
			}
			else
			{
				//Draw
				SpriteList[CurrentLayer_].at(i)->Draw();
			}
		}
		else
		{
			SpriteList[CurrentLayer_].erase(SpriteList[CurrentLayer_].begin()+ i);
		}
	}

	//Lets flip the screen using OpenGL-stuff
	SDL_GL_SwapBuffers();
	
	FPScounter();
}

GraphicCore * GraphicCore::GetInstance()
{
	if (thisGraphicCore_ == 0)
	{
		thisGraphicCore_ = new GraphicCore();
	}
	return thisGraphicCore_;
}

SDL_Surface * GraphicCore::GetScreen()
{
	return screen_;

}

int GraphicCore::GetScreenX(void)
{
	return screenX_;	
}

int GraphicCore::GetScreenY(void)
{
	return screenY_;	
}


void GraphicCore::ClearScreen(void)
{
	//Fill the screen with black color/clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();

}

void GraphicCore::RemoveAllSprites(void)
{
	for (int j = 0; j < LayersCount_; j++)
	{
		for (int i=0;i< SpriteList[j].size();i++)
		{
			if (SpriteList[j].at(i))
			{
				delete SpriteList[j].at(i);
				//SpriteList.at(i) = 0;	
			}	
		}
		SpriteList[j].clear();
	}
}

void GraphicCore::RemoveAllSpritesFromLayer(int layer)
{
	if (layer < LayersCount_ && layer >= 0)
	{
		for (int i=0;i< SpriteList[layer].size();i++)
		{
			if (SpriteList[layer].at(i))
			{
				delete SpriteList[layer].at(i);
				//SpriteList.at(i) = 0;	
			}	
		}
		SpriteList[layer].clear();
	}
}

void GraphicCore::SetCurrentLayer(int layer)
{
	if (layer < 0 || layer > LayersCount_ - 1)	
	{
		std::cerr << "Invalid Screen Layer in SetCurrentLayer, ignored!\n";
	}
	else
	{
		std::cout << "Screen layer set to " << layer << "!\n";
		CurrentLayer_ = layer;	
	}
}

int GraphicCore::GetCurrentLayer(void)
{
	return CurrentLayer_;	
}

int GraphicCore::GetLayerCount(void)
{
	return LayersCount_;	
}

void GraphicCore::AddSprite(Sprite * sprite)
{
	SpriteList[CurrentLayer_].push_back(sprite);	
}


void GraphicCore::FPScounter(void)
{
	long now = SDL_GetTicks();
	static long a = 0, b = 0, last = 0;
	a = a + now - last;
	b++;
	CurrentFPS_ = b;
	
	if (a >= 1000)
	{
		std::cout << "FPS: "<< b << std::endl;
		LastFPS_ = b;
		a=0;
		b=0;
		LastFPSUpdateTime_ = now;
	}
	last = now;	

}
