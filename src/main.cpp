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

#include <iostream>
#include <vector>
#include <SDL/SDL.h>

#include "Sync.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Object.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"
#include "GraphicCore.hpp"
#include "EventCore.hpp"
#include "Sound.hpp"
#include "SoundCore.hpp"
#include "FontCore.hpp"
#include "Scorebar.hpp"
#include "Map.hpp"
#include "Animation.hpp"
#include "Player.hpp"
#include "LogicCore.hpp"



const char *NAME_OF_GAME = "Teddi the Bear: Quest of Red Ribbon";
const double VERSION_OF_GAME = 0.2; 
const char *CREATOR_OF_GAME = "Mika 'ighea' Hynna";

int main(int argc, char *argv[])
{
	char captionchars[256];
	//"clear the caption"
	for (int i = 0;i< 256;i++)
	{
		captionchars[i]='\0';
	}
	strcat(captionchars, NAME_OF_GAME);
	strcat(captionchars, " v0.2 by ");
	strcat(captionchars, CREATOR_OF_GAME);
	
	std::cout << "Warming up " << NAME_OF_GAME << " version " << VERSION_OF_GAME << " by " << CREATOR_OF_GAME<< std::endl << std::endl; 
	
	int screenX = 640;
	int screenY = 480;
	int screenBPP = 24;



	//For the magic tricks
	long ticks = 0, now = 0;

	Sync *TimeShift = Sync::GetInstance();
	TimeShift->SetMaxSyncTime(200);

	GraphicCore *screen = GraphicCore::GetInstance();
	screen->Init(captionchars, screenX, screenY, screenBPP, 6);

	SoundCore *sounds = SoundCore::GetInstance();
	sounds->Init();

	FontCore *fonts = FontCore::GetInstance();
	fonts->Init();
	
	LogicCore *logics = LogicCore::GetInstance();
	

	SDL_Color color_green = {1,255,2}; //green
	SDL_Color color_orange = {241,112,0}; //orange
	
	TTF_Font *font8 = fonts->LoadFont("assets/font.ttf", 10);
	TTF_Font *font16 = fonts->LoadFont("assets/font.ttf", 16);
	TTF_Font *font24 = fonts->LoadFont("assets/font.ttf", 24);
	TTF_Font *font32 = fonts->LoadFont("assets/font.ttf", 32);
	
//Splashscreen stuff
	
	screen->SetCurrentLayer(0);
	Texture *splash_texture = new Texture("assets/splashscreen.bmp");
	Sprite *splash_sprite = new Sprite(splash_texture);
	splash_sprite->SetPosition(screen->GetScreenX()/2, screen->GetScreenY()/2);

	Texture *loading = new Texture(font24, "Loading..", solid, color_orange);
	Sprite *text_loading = new Sprite(loading);
	text_loading->SetPosition(text_loading->GetWidth(), screen->GetScreenY()-text_loading->GetHeight());
	text_loading->SetUseColorKey(true);
	screen->Update();
	text_loading->SetFreeMe();

//	screen->RemoveAllSpritesFromLayer(0);
	screen->SetCurrentLayer(5);
	Sprite *sprite_nextlevel;

	screen->SetCurrentLayer(1);

//Cleanup for game

	//Creating player object
	Player *player = new Player();

//CREATURE GEN
	Texture *texture_otus0 = new Texture("assets/otus0.bmp");
	Texture *texture_otus1 = new Texture("assets/otus1.bmp");
	Texture *texture_otus2 = new Texture("assets/otus2.bmp");
	Texture *texture_otus3 = new Texture("assets/otus3.bmp");

	Creature *criit = new Creature(-100,-100, Random(0,359), 50, 10, 10, false, true);

	Sprite *criit_move = new Sprite(texture_otus1);
	criit_move->Append(texture_otus2);
	criit_move->Append(texture_otus0);
	criit_move->Append(texture_otus3);
	criit_move->SetUseColorKey(true);

	Sprite *criit_idle = new Sprite(texture_otus0);
	criit_idle->SetUseColorKey(true);

	criit->SetAnimation(new Animation(criit_idle, criit_move));

	criit->SetIsAggressive(true);
	criit->SetTurningSpeed(200);
	criit->SetIsAIEnabled(true);
	
	criit->SetDamagedSound(new Sound("assets/groan.wav"));
	criit->SetEnemy(player);
	criit->SetBloodSprite(new Sprite(new Texture("assets/red_bloodsplash.bmp")));
//CREATURE GEN END

	
	Weapon *flame_breath = new Weapon(1,50,1,200,0);
	Sprite *sprite_flame_breath = new Sprite(new Texture("assets/flame_breath.bmp"));
	sprite_flame_breath->SetPosition(-123123,-1321312,0);
	flame_breath->SetWeaponSprite(sprite_flame_breath);
	flame_breath->SetOwner(criit);
	flame_breath->SetBulletSprite(new Sprite(new Texture("assets/fireball.bmp")));
	criit->SetWeapon(flame_breath);
	
	//Trees
	Placeable *placeable_tree = new Placeable(10,10,Random(1,359));
	placeable_tree->SetSprite(new Sprite(new Texture("assets/tree0.bmp")));
	Placeable *placeable_tree2 = new Placeable(10,10,Random(1,359));
	placeable_tree2->SetSprite(new Sprite(new Texture("assets/tree1.bmp")));

	//Sandpit
	Placeable *placeable_sand = new Placeable(10,10,Random(1,359));
	placeable_sand->SetSprite(new Sprite(new Texture("assets/sand.bmp")));
	placeable_sand->SetIsGround(true);

	//Footprints
	Placeable *placeable_footprints = new Placeable(10,10,Random(1,359));
	placeable_footprints->SetSprite(new Sprite(new Texture("assets/footprints.bmp")));
	placeable_footprints->SetIsGround(true);

	//Bond
	Placeable *placeable_bond = new Placeable(10,10,Random(1,359));
	placeable_bond->SetSprite(new Sprite(new Texture("assets/bond.bmp")));
	placeable_bond->SetIsGround(true);

	//Icelake
	Placeable *placeable_icelake = new Placeable(10,10,Random(1,359));
	placeable_icelake->SetSprite(new Sprite(new Texture("assets/icelake.bmp")));
	placeable_icelake->SetIsGround(true);

	//Bond
	Placeable *placeable_deadtree = new Placeable(10,10,Random(1,359));
	placeable_deadtree->SetSprite(new Sprite(new Texture("assets/deadtree.bmp")));

	//Door
	Placeable *placeable_door = new Placeable(10,10,0);
	placeable_door->SetSprite(new Sprite(new Texture("assets/door.bmp")));
	placeable_door->SetIsGround(true);

	//cave
	Placeable *placeable_cave = new Placeable(10,10,0);
	placeable_cave->SetSprite(new Sprite(new Texture("assets/cave0.bmp")));
	placeable_cave->SetIsGround(true);


	//End point
/*	Placeable *finish = new Placeable(-123,113,0);
	finish->SetSprite(new Sprite(new Texture("assets/cave0.bmp")));
	finish->SetIsGround(true);
	finish->SetPosition(-123,-123,0);
*/

	Creature *finish = new Creature(-124142,-124141,0);
	Sprite *finish_idle = new Sprite(new Texture("assets/bat0.bmp"));
	finish_idle->SetUseColorKey(true);
	Sprite *finish_moving = new Sprite(new Texture("assets/bat1.bmp"));
	finish_moving->Append(new Texture("assets/bat2.bmp"));
	finish_moving->Append(new Texture("assets/bat3.bmp"));
	finish_moving->SetUseColorKey(true);
	finish->SetAnimation(new Animation(finish_idle, finish_moving));
	finish->SetVelocity(120);
	finish->SetIsAggressive(true);
	finish->SetIsAIEnabled(true);
	finish->SetBloodSprite(new Sprite(new Texture("assets/red_bloodsplash.bmp")));
	finish->SetDamagedSound(new Sound("assets/ih.wav"));
	
	Weapon *wave = new Weapon(1, 32, 2, 200, +0);
	Sprite *sprite_wave = new Sprite(new Texture("assets/wave0.bmp"));
	sprite_wave->Append(new Texture("assets/wave1.bmp"));
	sprite_wave->Append(new Texture("assets/wave2.bmp"));
	wave->SetWeaponSprite(sprite_wave);
	sprite_wave->SetPosition(-12313223,-12312132,0);
//	wave->SetBulletSprite(new Sprite(new Texture("assets/bullet0.bmp")));
	Sound *sound_wave = new Sound("assets/wave.wav");
	wave->SetWeaponSound(sound_wave);
	finish->SetWeapon(wave);	


/// SNOWMAN

	Creature *snowman = new Creature(-100,-100, Random(0,359), 50, 10, 10, false, true);

	Sprite *snowman_move = new Sprite(new Texture("assets/snowman0.bmp"));
	snowman_move->Append(new Texture("assets/snowman1.bmp"));
	snowman_move->Append(new Texture("assets/snowman0.bmp"));
	snowman_move->Append(new Texture("assets/snowman2.bmp"));
	snowman_move->SetUseColorKey(true);

	Sprite *snowman_idle = new Sprite(new Texture("assets/snowman0.bmp"));
	snowman_idle->SetUseColorKey(true);

	snowman->SetAnimation(new Animation(snowman_idle, snowman_move));

	snowman->SetIsAggressive(true);
	snowman->SetTurningSpeed(190);
	snowman->SetIsAIEnabled(true);
	
	snowman->SetDamagedSound(new Sound("assets/groan.wav"));
	snowman->SetEnemy(player);
	snowman->SetBloodSprite(new Sprite(new Texture("assets/snow_blood.bmp")));
	
	Weapon *coal_gun = new Weapon(1,50,1,160,0);
	coal_gun->SetOwner(snowman);
	coal_gun->SetBulletSprite(new Sprite(new Texture("assets/coalball.bmp")));
	snowman->SetWeapon(coal_gun);
	coal_gun->SetWeaponSound(new Sound("assets/weapon_swing0.wav"));


// GHOST


	Creature *ghost = new Creature(-100,-100, Random(0,359), 50, 16, 16, false, true);

	Sprite *ghost_move = new Sprite(new Texture("assets/ghost1.bmp"));
	ghost_move->Append(new Texture("assets/ghost2.bmp"));
	ghost_move->Append(new Texture("assets/ghost3.bmp"));
	ghost_move->SetUseColorKey(true);

	Sprite *ghost_idle = new Sprite(new Texture("assets/ghost0.bmp"));
	ghost_idle->SetUseColorKey(true);

	ghost->SetAnimation(new Animation(ghost_idle, ghost_move));

	ghost->SetIsAggressive(true);
	ghost->SetTurningSpeed(250);
	ghost->SetIsAIEnabled(true);
	ghost->SetVelocity(100);
	
	ghost->SetDamagedSound(new Sound("assets/groan.wav"));
	ghost->SetEnemy(player);
	ghost->SetBloodSprite(new Sprite(new Texture("assets/ghostblood.bmp")));
	
	Weapon *beam = new Weapon(1,30,1,160,0);
	beam->SetOwner(ghost);
	beam->SetWeaponSprite(new Sprite(new Texture("assets/ghostbeam.bmp")));
	beam->SetBulletSprite(new Sprite(new Texture("assets/ghostbeam.bmp")));
	beam->SetWeaponSound(new Sound("assets/wave.wav"));
	ghost->SetWeapon(beam);

	
////////////// PLAYER /////////////
	Sprite *player_move = new Sprite(new Texture("assets/teddy1.bmp"), -1,4);
	player_move->Append(new Texture("assets/teddy0.bmp"));
	player_move->Append(new Texture("assets/teddy2.bmp"));
	player_move->Append(new Texture("assets/teddy0.bmp"));
	player_move->SetUseColorKey(true);

	Sprite *player_idle = new Sprite(new Texture("assets/teddy0.bmp"));
	player_idle->SetUseColorKey(true);
	player->SetVelocity(100);
	player->SetAngle(Random(1,359));
	
	player->SetAnimation(new Animation(player_idle, player_move));
	player->SetIsAIEnabled(false);
	
	player->SetHP(10);
	player->SetBloodSprite(new Sprite(new Texture("assets/white_bloodsplash.bmp")));
	player->SetDamagedSound(new Sound("assets/uff.wav"));

	finish->SetEnemy(player);

/////////////////////////////

	Weapon *thegun = new Weapon(5, 100, 0.3, 200, +0);
	thegun->SetWeaponSprite(new Sprite(new Texture("assets/guneffect0.bmp")));
	thegun->SetBulletSprite(new Sprite(new Texture("assets/bullet0.bmp")));
	Sound *weapon_sound = new Sound("assets/weapon_swing0.wav");
	thegun->SetWeaponSound(weapon_sound);
	player->SetWeapon(thegun);	

	EventCore *events = EventCore::GetInstance();

//	events->SetPlayer(player);
	
	int state, x, y;
	Sprite *mouse = new Sprite(new Texture("assets/testo.bmp"));
	mouse->SetUseColorKey(true);
	mouse->Append(new Texture("assets/testo2.bmp"));
	mouse->SetPosition(screenX/2, screenY/2);

	Sound *backgroundmusic = new Sound("assets/music.wav");
	

//	Scorebar *hitpoints = new Scorebar("HP:", font16, player->GetHP(),color_orange, 0, 0);
	Scorebar *hitpoints = new Scorebar(new Texture("assets/heart.bmp"),5,0,0);
	hitpoints->SetPosition(screenX - hitpoints->GetWidth(), hitpoints->GetHeight()>>1);


//MENU stuff
	screen->SetCurrentLayer(2);
	Texture *menu_texture = new Texture("assets/splashscreen.bmp");
	Sprite *menu_bg = new Sprite(menu_texture);
	menu_bg->SetPosition(screen->GetScreenX()/2, screen->GetScreenY()/2);

	Texture *menu_start = new Texture(font32, "Start", solid, color_green);
	Texture *menu_story = new Texture(font32, "Story", solid, color_green);
	Texture *menu_exit = new Texture(font32, "Exit", solid, color_green);
	Sprite *menu_sprite_start = new Sprite(menu_start);
	menu_sprite_start->SetUseColorKey(true);
	Sprite *menu_sprite_story = new Sprite(menu_story);
	menu_sprite_story->SetUseColorKey(true);
	Sprite *menu_sprite_exit = new Sprite(menu_exit);
	menu_sprite_exit->SetUseColorKey(true);
	
	Sprite *menu_bearhead = new Sprite(new Texture("assets/bearhead.bmp"));
	menu_bearhead->SetUseColorKey(true);
	
//MENU end



//STORY stuff
	screen->SetCurrentLayer(3);
	Sprite *story1 = new Sprite(new Texture(font16, "In the middle of the night Teddi's beloved red ribbon was stolen." , solid, color_green)); 
	Sprite *story2 = new Sprite(new Texture(font16, "Only seen a flash of the robber, Teddi grapped an apple" , solid, color_green)); 
	Sprite *story3 = new Sprite(new Texture(font16, "basket nearby and headed out!" , solid, color_green)); 
	Sprite *story4 = new Sprite(new Texture(font16, "The night was dark but Teddi could see a black figure " , solid, color_green)); 
	Sprite *story5 = new Sprite(new Texture(font16, "diseppearing in to the darknes." , solid, color_green)); 
	Sprite *story6 = new Sprite(new Texture(font16, "Teddi knew that there was no time to waste..." , solid, color_green)); 
//STORY end

//The gAME END SCREEN
	screen->SetCurrentLayer(4);
	Sprite *sprite_gameend = new Sprite(new Texture("assets/theend.bmp"));
	sprite_gameend->SetPosition(screen->GetScreenX()/2, screen->GetScreenY()/2);

//Loading done...

//Update loading screen...
	screen->SetCurrentLayer(0);
	screen->Update();
	text_loading = new Sprite(new Texture(font24, "Loading.. Ok! Press any key..", solid, color_orange));
	text_loading->SetPosition(text_loading->GetWidth()/2+65, screen->GetScreenY()-text_loading->GetHeight());
	text_loading->SetUseColorKey(true);
	screen->Update();
	SDL_Delay(1);
	events->WaitForKeyPress();

	screen->SetCurrentLayer(2);

//Map maker
	Map *area = Map::GetInstance();
	int map_level = 0;
	Sound *sound_endgame = new Sound("assets/wippii.wav");

	int menu_current = 0;
	int menu_count = 3;
	Keyboard *keys = Keyboard::GetInstance();

	while (!events->GetIsExitKeyPressed()) //MEnu starts
	{
		events->Update();
		SDL_Delay(10);
		
		menu_sprite_start->SetPosition(screen->GetScreenX()/2+menu_sprite_start->GetWidth()/2,
		screen->GetScreenY()/3 + 3*screen->GetScreenY()/8);
		menu_sprite_story->SetPosition(screen->GetScreenX()/2+menu_sprite_story->GetWidth()/2,
		screen->GetScreenY()/3 + 4*screen->GetScreenY()/8);
		menu_sprite_exit->SetPosition(screen->GetScreenX()/2+menu_sprite_exit->GetWidth()/2,
		screen->GetScreenY()/3 + 5*screen->GetScreenY()/8);
		menu_bearhead->SetPosition(screen->GetScreenX()/2-menu_bearhead->GetWidth(),
		screen->GetScreenY()/3 + (menu_current+3)*screen->GetScreenY()/8 - 10);

		if (menu_current == 0)
		{
			menu_sprite_start->SetScale(1);
		}
		else 
		{
			menu_sprite_start->SetScale(0.8);
		}
		if (menu_current == 1)
		{
			menu_sprite_story->SetScale(1);
		}
		else 
		{
			menu_sprite_story->SetScale(0.8);
		}
		if (menu_current == 2)
		{
			menu_sprite_exit->SetScale(1);
		}
		else 
		{
			menu_sprite_exit->SetScale(0.8);
		}
		
		screen->Update();
		if (keys->GetIsDown(SDLK_UP))
		{
			keys->SetKeyState(SDLK_UP,false);
			menu_current--;
			if (menu_current < 0) menu_current = menu_count - 1;	
		}
		if (keys->GetIsDown(SDLK_DOWN))
		{
			keys->SetKeyState(SDLK_DOWN,false);
			menu_current++;
			if (menu_current > menu_count -1) menu_current = 0;	
		}
		

		if (keys->GetIsDown(SDLK_RETURN))
		{
			keys->SetKeyState(SDLK_RETURN, false);
			switch (menu_current)
			{
			case 1: //the story M;E
				menu_bg->SetFadeAway();
				menu_bg->SetUseColorKey(true);
				menu_sprite_story->SetFadeAway();
				menu_sprite_start->SetFadeAway();
				menu_sprite_exit->SetFadeAway();
				menu_bearhead->SetFadeAway();
				while (menu_bg->GetAlphaLevel() > 0)
				{
					TimeShift->Update();
					screen->Update();
					SDL_Delay(10);
				}
				menu_bg->SetAlphaLevel(1);
				menu_sprite_start->SetAlphaLevel(1);
				menu_sprite_story->SetAlphaLevel(1);
				menu_sprite_exit->SetAlphaLevel(1);
				menu_bearhead->SetAlphaLevel(1);
				menu_bg->SetFadeAwayOff();
				menu_bg->SetUseColorKey(false);
				menu_sprite_story->SetFadeAwayOff();
				menu_sprite_start->SetFadeAwayOff();
				menu_sprite_exit->SetFadeAwayOff();
				menu_bearhead->SetFadeAwayOff();
				
				std::cout << "Entered the story dialog\n";
				screen->SetCurrentLayer(3);
				story1->SetPosition(story1->GetWidth()/2,story1->GetHeight());
				story2->SetPosition(story2->GetWidth()/2,story1->GetHeight()*2);
				story3->SetPosition(story3->GetWidth()/2,story1->GetHeight()*3);
				story4->SetPosition(story4->GetWidth()/2,story1->GetHeight()*4);
				story5->SetPosition(story5->GetWidth()/2,story1->GetHeight()*5);
				story6->SetPosition(story6->GetWidth()/2,story1->GetHeight()*7);
				screen->Update();
				SDL_Delay(1000);
				events->WaitForKeyPress();
				screen->SetCurrentLayer(2); //back to menu layer
			break;
			case 2:
				std::cout << "Quiting..\n";
				menu_bg->SetFadeAway();
				menu_bg->SetUseColorKey(true);
				menu_sprite_story->SetFadeAway();
				menu_sprite_start->SetFadeAway();
				menu_sprite_exit->SetFadeAway();
				menu_bearhead->SetFadeAway();
				while (menu_bg->GetAlphaLevel() > 0)
				{
					TimeShift->Update();
					screen->Update();
					SDL_Delay(10);
				}
				events->SetIsExitKeyPressed(true);
			break;
			case 0:	
				menu_bg->SetFadeAway();
				menu_bg->SetUseColorKey(true);
				menu_sprite_story->SetFadeAway();
				menu_sprite_start->SetFadeAway();
				menu_sprite_exit->SetFadeAway();
				menu_bearhead->SetFadeAway();
				while (menu_bg->GetAlphaLevel() > 0)
				{
					TimeShift->Update();
					screen->Update();
					SDL_Delay(10);
				}
				menu_bg->SetAlphaLevel(1);
				menu_sprite_start->SetAlphaLevel(1);
				menu_sprite_story->SetAlphaLevel(1);
				menu_sprite_exit->SetAlphaLevel(1);
				menu_bg->SetFadeAwayOff();
				menu_bg->SetUseColorKey(false);
				menu_sprite_story->SetFadeAwayOff();
				menu_sprite_start->SetFadeAwayOff();
				menu_sprite_exit->SetFadeAwayOff();
				menu_bearhead->SetAlphaLevel(1);
				menu_bearhead->SetFadeAwayOff();

				
				// ####################GAME ON! ###############################
				screen->SetCurrentLayer(1); //Set the game screen layer
				map_level = 0;
				////////////////// MAP ///////////////
				finish->SetHP(50);
				finish_idle->SetAlphaLevel(1);
				finish_moving->SetAlphaLevel(1);
				finish_idle->SetFadeAwayOff();
				finish_moving->SetFadeAwayOff();
				finish->SetIsDead(false);
				player->SetIsDead(false);
				snowman->SetIsDead(false);
				snowman->SetHP(11);
				ghost->SetIsDead(false);
				ghost->SetHP(16);
				
				area->Init(40,30, "assets/grassland.bmp");
				criit->SetIsAIEnabled(true);
				area->SetBackground(new Texture("assets/map_background.bmp"));
				area->AppendCreature(criit,30);
				area->AppendPlaceable(placeable_footprints,15);
				area->AppendPlaceable(placeable_tree2, 50);
				area->AppendPlaceable(placeable_bond,20);
				area->AppendPlaceable(placeable_tree,170);
				area->SetEndPlaceable(placeable_cave);
				area->SetStartPoint(Random(1,area->GetSizeX()),Random(1,area->GetSizeY()));
				area->SetEndPoint(Random(1,area->GetSizeX()),Random(1,area->GetSizeY()));	
				area->SetPlayer(player);
				finish->SetIsAIEnabled(true);
				area->GenerateMap();
				
				//Redraw player animations
				player_move = new Sprite(new Texture("assets/teddy1.bmp"), -1,4);
				player_move->Append(new Texture("assets/teddy0.bmp"));
				player_move->Append(new Texture("assets/teddy2.bmp"));
				player_move->Append(new Texture("assets/teddy0.bmp"));
				player_move->SetUseColorKey(true);

				player_idle = new Sprite(new Texture("assets/teddy0.bmp"));
				player_idle->SetUseColorKey(true);
				player->SetVelocity(100);
				player->SetAngle(Random(1,359));
				player->SetAnimation(new Animation(player_idle, player_move));

				
				hitpoints->Update(1);
				player->SetIsDead(false);
				player->SetHP(10);
				hitpoints->Update(player->GetHP());
				std::cout << "Go!\n";
				screen->Update();
				//SDL_Delay(1);
				//Background music on!
				backgroundmusic->Play(-1);
			//	player->BringUp();

				//Main loop begins
				while (!events->GetIsExitKeyPressed())
				{
					if (player->GetHP() < 1) events->SetIsExitKeyPressed(true);
			
					//Update the gameloop sync-time
					TimeShift->Update();			

					//Hitpointsbar update
					hitpoints->Update(player->GetHP());
					events->Update();
					logics->Update();
					area->Update();
					screen->Update();

					//Magical delay to not consume all CPU time & FPS calculator
					now = SDL_GetTicks();
					if ((now - ticks) < 10)
					{
						SDL_Delay(5);
					}
					ticks = now;

					//Some mouse stuff to be removed soon...	
					SDL_GetMouseState(&x,&y);
					mouse->SetPosition(x,y);
					
					if (area->GetMapEnded() && map_level == 2)
					{
						
						events->SetIsExitKeyPressed(true);
						std::cout << "Evil bat defeated!\n";
						sounds->StopAllAudio();
						sound_endgame->Play();
						screen->SetCurrentLayer(4);
						SDL_Delay(2000);
						screen->Update();
						SDL_Delay(4000);
						events->WaitForKeyPress();
						
					}
					else if (area->GetMapEnded())
					{
						map_level++; //Next level!	
						area->ClearMap();
						logics->Update();
						area->ClearObjectLists();
						
						std::cout << "Level :" << map_level << "!\n";
						//Next level thingies!
						screen->SetCurrentLayer(5);
						if (map_level == 1)
						{
							sprite_nextlevel = new Sprite(new Texture(font16,"the Snowland...",solid,color_orange));
						}
						if (map_level == 2)
						{
							sprite_nextlevel = new Sprite(new Texture(font16,"the Deadland...",solid,color_orange));
						}
						sprite_nextlevel->SetPosition(screen->GetScreenX()/3,
						screen->GetScreenY()/3);
						screen->Update();
						screen->Update();
						sprite_nextlevel->SetFreeMe();
						SDL_Delay(3000);
						//events->WaitForKeyPress();
						screen->SetCurrentLayer(1);
						//Continue with map generation:

						if (map_level == 1)
						{
							area->Init(20,30, "assets/snowground.bmp");
							area->AppendCreature(snowman,20);
							area->AppendPlaceable(placeable_deadtree,40);
							area->AppendPlaceable(placeable_tree,20);
							area->AppendPlaceable(placeable_footprints,15);
							area->AppendPlaceable(placeable_icelake,15);
							area->SetStartPoint(Random(1,area->GetSizeX()),Random(1,area->GetSizeY()));
							area->SetEndPoint(Random(1,area->GetSizeX()),Random(1,area->GetSizeY()));	
							area->SetPlayer(player);
//							area->SetBackground(new Texture("assets/map_background.bmp"));
							finish->SetIsAIEnabled(true);
//							area->SetEndCreature(finish);
							area->SetEndPlaceable(placeable_door);
							area->GenerateMap();
						}
						if (map_level == 2)
						{
							area->Init(30,20, "assets/deathland.bmp");
							area->AppendCreature(ghost, 10);
							area->AppendPlaceable(placeable_sand, 15);
							area->AppendPlaceable(placeable_footprints,10);
							area->AppendPlaceable(placeable_deadtree,50);
							area->SetEndCreature(finish);
							area->SetStartPoint(Random(1,area->GetSizeX()),Random(1,area->GetSizeY()));
							area->SetEndPoint(Random(1,area->GetSizeX()),Random(1,area->GetSizeY()));	
							area->SetPlayer(player);
							area->GenerateMap();
	
							
						}
							//Redraw player animations
							player_move = new Sprite(new Texture("assets/teddy1.bmp"), -1,4);
							player_move->Append(new Texture("assets/teddy0.bmp"));
							player_move->Append(new Texture("assets/teddy2.bmp"));
							player_move->Append(new Texture("assets/teddy0.bmp"));
							player_move->SetUseColorKey(true);

							player_idle = new Sprite(new Texture("assets/teddy0.bmp"));
							player_idle->SetUseColorKey(true);
							player->SetVelocity(100);
							player->SetAngle(Random(1,359));
							player->SetAnimation(new Animation(player_idle, player_move));
							player->HaltAllMovement();
							hitpoints->Update(1);
							hitpoints->Update(player->GetHP());
					}
				}
				//Main loop ends

				if (player->GetHP() <= 0)
				{
					sounds->StopAllAudio();
					std::cout << "Omgh... ur dead!\n";
					screen->SetCurrentLayer(3);
		
					Texture *youfuckingdied = new Texture(font32, "Teddi is burned to ashes!", solid, color_orange);	
					Sprite *yfd_sprite = new Sprite(youfuckingdied, -1,0,true,true);
					yfd_sprite->SetPosition(screen->GetScreenX()>>1,screen->GetScreenY()>>1);	

					Texture *youfuckingdied2 = new Texture(font32, "The End..", shaded, color_green);	
					Sprite *yfd_sprite2 = new Sprite(youfuckingdied2, -1,0,true,true);
					yfd_sprite2->SetPosition(screen->GetScreenX()>>1,screen->GetScreenY()/2 + 100);
		
					Sound *game_end = new Sound("assets/game_end.wav");
					game_end->Play(0,-1);
					SDL_Delay(1000);
					screen->Update();
					SDL_Delay(3000);
				}

				map_level = 0; //Reset map level!
				
				events->SetIsExitKeyPressed(false);
				screen->SetCurrentLayer(2); //Set the menu screen layer
				sounds->StopAllAudio();
				//Clearing map:
				area->ClearMap();
				logics->Update();
				area->ClearObjectLists();
				criit->SetIsAIEnabled(false);
				finish->SetIsAIEnabled(false);

				break;
		
				default:
			
				break;
			}
		}
//###################GAME LOOP END! ########################
	} //Menu ends..

	
	std::cout << "\n***** QUIT *****\nCleaning remaining stuff:\n";
	delete logics;
	delete events;
	delete sounds;
	delete screen;
	delete TimeShift;
	
	std::cout << "\nEXIT SUCCESS!" << std::endl;
	
	std::cout << "\nThanks for trying!\n Created by Mika 'ighea' Hynnä 2007\n http://mika.wippiesblog.com\n\n";
	
	return 0;
}
