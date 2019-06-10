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

#ifndef _SOUNDCORE_HPP
#define _SOUNDCORE_HPP

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <vector>
#include "Sound.hpp"

class Sound;

class SoundCore
{
private:
	static SoundCore *thisSoundCore_;
	
	int audio_rate_;
	Uint16 audio_format_;
	int audio_channels_;
	int audio_buffers_;
 
 	std::vector <Sound *> SoundList;
 
	SoundCore();
public:
	static SoundCore * GetInstance(void);
	~SoundCore();
	void Init(int audio_rate = 22050, Uint16 audio_format = AUDIO_S16SYS, int audio_channels = 2, int audio_buffers = 4096);
	void UnloadAllSounds(void);
	
	void AppendSoundToList(Sound *sound);
	
	void StopAllAudio(void);

};



#endif
