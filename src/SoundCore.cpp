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

#include "SoundCore.hpp"

SoundCore *SoundCore::thisSoundCore_ = 0;

SoundCore::~SoundCore()
{
	std::cout << "Freeing SoundCore..\n";
	
	UnloadAllSounds();
	
	//Closing audio
	Mix_CloseAudio();
	
	std::cout << "Done.\n";
}

SoundCore::SoundCore()
{
	std::cout << "SoundCore created." << std::endl;	
}


SoundCore * SoundCore::GetInstance(void)
{
	if (thisSoundCore_ == NULL || thisSoundCore_ == 0)
	{
		thisSoundCore_ = new SoundCore();
	}
	return thisSoundCore_;	
}

void SoundCore::Init(int audio_rate, Uint16 audio_format, int audio_channels, int audio_buffers)
{
	std::cout << "Initializing SoundCore..";

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
	else
	{
		std::cout << "OK!\n";	
	}
	
}

void SoundCore::UnloadAllSounds(void)
{
	for (int i=0; i < SoundList.size(); i++)
	{
		if (SoundList.at(i))
		{
				delete SoundList.at(i);
		}	
	}	
	SoundList.clear();
}

void SoundCore::AppendSoundToList(Sound *sound)
{
	SoundList.push_back(sound);	
}

void SoundCore::StopAllAudio(void)
{
	Mix_HaltChannel(-1);
}
