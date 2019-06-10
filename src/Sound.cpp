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


#include "Sound.hpp"

Sound::Sound(const char sound_file[])
{
	sound_ = 0;
	music_ = 0;
	
	SoundCore::GetInstance()->AppendSoundToList(this);
	
	if (strstr(sound_file, ".ogg") != NULL)
	{
		music_ = Mix_LoadMUS(sound_file);
		if(music_ == NULL) {
			fprintf(stderr, "Unable to load Ogg file: %s\n", Mix_GetError());
		}	
	
	}
	else if (strstr(sound_file, ".wav") != NULL)
	{
		sound_ = Mix_LoadWAV(sound_file);
		if(sound_ == NULL) {
			fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
		}	
	}
	else
	{
		fprintf(stderr, "Unable to load sound file: Unknown format!\n");
		return;
	}
	
	std::cout << "Loaded sound file " << sound_file << "\n";
	//Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
//	SoundCore::GetInstance()->SoundList.push_back(this);
}


Sound::~Sound()
{
	if (sound_) Mix_FreeChunk(sound_);
	if (music_) Mix_FreeMusic(music_);
	std::cout << "Unloaded sound file!\n";
}

int Sound::Play(int loops, int channel)
{
	if (sound_ != 0 && sound_ != NULL)
	{
		if (Mix_PlayChannel(channel, sound_, loops) == -1)
		{
			fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
			return -1;
		}
	}
	else if (music_ != 0 && music_ != NULL)
	{
		if(Mix_PlayMusic(music_, loops) == -1) 
		{
			fprintf(stderr, "Unable to play Ogg file: %s\n", Mix_GetError());
			return -1;
		}
	}
	else 
	{
		fprintf(stderr, "Unable to play sound file: %s\n", Mix_GetError());
		return -1;
	}
	
	return 0;
}
