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

#include "EventCore.hpp"

EventCore * EventCore::thisEventCore_ = 0;

EventCore *EventCore::GetInstance(void)
{
	if (thisEventCore_ == 0)
	{
		thisEventCore_ = new EventCore();
	}
	return thisEventCore_;
}

	
EventCore::EventCore()
{
	std::cout << "EventCore created.\n";
	isExitKeyPressed_ = false;
	std::cout << "Event handlers created!" << std::endl;	
}

EventCore::~EventCore()
{

	std::cout << "Freeing EventCore...\n";

	std::cout << "\nDone.\n";
}

void EventCore::Update(void)
{
	
	
	//EVENTS
	while(SDL_PollEvent(&event_))
	{
		switch(event_.type)
		{
				// Handle keyboard events
				
				
				//KEY DOWN EVENTS
				case SDL_KEYDOWN:
					//Update Keyboard's states
					Keyboard::GetInstance()->SetKeyState(event_.key.keysym.sym,true);
					
					switch (event_.key.keysym.sym ) 
					{
						case SDLK_ESCAPE:
							isExitKeyPressed_ = true;
						break;
						case SDLK_SPACE:
						break;
						case SDLK_RETURN:
						break;
						case SDLK_LCTRL:
						break;
						case SDLK_UP:
						break;
						case SDLK_DOWN:
						break;
						case SDLK_LEFT:
						break;
						case SDLK_RIGHT:
						break;

						default:
						break;
					}

				break;

				//KEY UP EVENTS
				case SDL_KEYUP:
					//Update Keyboard's states
					Keyboard::GetInstance()->SetKeyState(event_.key.keysym.sym,false);

					// Handle keyboard events
					switch (event_.key.keysym.sym ) 
					{
						case SDLK_LCTRL:
						break;
						case SDLK_UP:
						break;
						case SDLK_DOWN:
						break;
						case SDLK_LEFT:
						break;
						case SDLK_RIGHT:
						break;

						default:
						break;
					}
				
            	break;

        		case SDL_QUIT:
            		/* Handle quit requests (like Ctrl-c). */
            		isExitKeyPressed_ = true;
            	break;
				
				case SDL_MOUSEMOTION:
					//Mouse moved!
				break;
	
				case SDL_MOUSEBUTTONDOWN:
					//controllableObject->IsDamaged(1);
					//if (SDL_MouseButtonEvent.button == SDL_BUTTON_LEFT) std::cout << "hiiri!\n";
				break;
				case SDL_MOUSEBUTTONUP:
				break;
			
				default:
				break;
		}
	}
		
}

bool EventCore::GetIsExitKeyPressed(void)
{
	return isExitKeyPressed_;	
}

void EventCore::SetIsExitKeyPressed(bool state)
{
	isExitKeyPressed_ = state;	
}

void EventCore::WaitForKeyPress(void)
{
	SDL_Event event_;
	bool pressed = false;
	
	while (!pressed)
	{
		while(SDL_PollEvent(&event_))
		{
			switch(event_.type)
			{
				case SDL_KEYDOWN:
					pressed = true;
				break;
				case SDL_MOUSEBUTTONDOWN:
					pressed = true;
				break;
				default:
				break;
			}
		}
	}
}
