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

#include "Texture.hpp"

Texture::Texture(const char bmp_file[], int colorkeyR, int colorkeyG, int colorkeyB)
{
	texture_ = 0;
	w_ = 1;
	h_ = 1;

	SDL_Surface *tempTexture = 0;

	std::cout << "Loading file " << bmp_file << " as texture.." << std::endl;

	tempTexture = SDL_LoadBMP(bmp_file);
	if (tempTexture == NULL)
	{
		std::cerr << "Couldn't load file: " << bmp_file << "!" << std::endl;
		return;
	}
	else
	{
		//Set white(default) as transparent color by using color keying
		SDL_SetColorKey(tempTexture, SDL_SRCCOLORKEY, SDL_MapRGB(tempTexture->format, colorkeyR, colorkeyG, colorkeyB));
	}

	CreateTexture(tempTexture);

}


Texture::Texture(TTF_Font *font, const char text[],textquality quality ,SDL_Color color, int colorkeyR , int colorkeyG , int colorkeyB)
{
	texture_ = 0;
	w_ = 1;
	h_ = 1;
	
	SDL_Surface *tempTexture = 0;

	if (quality == solid) 
	{
		tempTexture = TTF_RenderText_Solid(font, text, color);
	}
	else if (quality == shaded) 
	{
		tempTexture = TTF_RenderText_Shaded(font, text, color, color);
	}
	else if (quality == blended) 
	{
		tempTexture = TTF_RenderText_Blended(font, text, color);
	}

	if (tempTexture == 0)
	{
		std::cerr << "Couldn't create text surface... ;<" << std::endl;
		return;
	}
	else
	{
		//Set white(default) as transparent color by using color keying
		SDL_SetColorKey(tempTexture, SDL_SRCCOLORKEY, SDL_MapRGB(tempTexture->format, colorkeyR, colorkeyG, colorkeyB));
	}

	CreateTexture(tempTexture);
}

Texture::~Texture()
{
	if (texture_ != 0 || texture_ != NULL)
	{
	//Destroing texture
		std::cout << "Destroing texture..."<< std::endl;
		glDeleteTextures(1, texture_);
		texture_ = 0;
	}
}

GLuint * Texture::GetTexture()
{
	if (texture_ != 0 || texture_ != NULL)
//	if (texture_)
	{
		return texture_;
	}
	
	std::cerr << "Texture not loaded... might be a problem..." << std::endl;
	return NULL;

}

int Texture::GetH()
{
	return h_;
}

int Texture::GetW()
{
	return w_;
}


void Texture::CreateTexture(SDL_Surface *tempTexture)
{
	//Create texture
	texture_ = new GLuint();
	glGenTextures(1, texture_);
	glBindTexture(GL_TEXTURE_2D, *texture_);

	const Uint32
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000, gmask = 0x00ff0000, bmask = 0x0000ff00, amask = 0x000000ff;
	#else
		rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000;
	#endif
	Uint32 w, h;

	//Lets find the nearest power-of-two for the tempTexture SDL_Surface, OpenGL's restriction for textures
	for (w = 1; w < tempTexture->w; w <<= 1);
	for (h = 1; h < tempTexture->h; h <<= 1);

	//Creating helper Surface in chosen color format: 32-bit RGBA
	SDL_Surface *helperSurface;
	helperSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, rmask, gmask, bmask, amask);
	//SDL_SetColorKey(helperSurface, SDL_SRCCOLORKEY, SDL_MapRGB(helperSurface->format, 255, 255, 255));
	//Texture bitmap to the helper surface
	SDL_BlitSurface(tempTexture, 0, helperSurface, 0);

//Set texture streching values
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //GL_LINEAR
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	//Creating texture from helper surface
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, helperSurface->pixels);

	//Release helper surfaces
	SDL_FreeSurface(helperSurface); 
	SDL_FreeSurface(tempTexture);

	//store height and width of the texture
	w_ = w;
	h_ = h;
	
}
