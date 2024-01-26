#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Scene2.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Physics.h"
#include "Entity.h"
#include "../bat.h"
#include "Tree.h"

#include "GuiControl.h"
#include "GuiManager.h"
#include "Defs.h"
#include "Log.h"

#include "SDL_mixer/include/SDL_mixer.h"

Scene2::Scene2() : Module()
{
	name.Create("scene2");
}

// Destructor
Scene2::~Scene2()
{}

// Called before render is available
bool Scene2::Awake(pugi::xml_node& config)
{
	if (active == true) {
		LOG("Loading Scene");
		bool ret = true;


		// iterate all objects in the scene
		// Check https://pugixml.org/docs/quickstart.html#access

		
	}
	return true;
	
}

// Called before the first frame
bool Scene2::Start()
{
	

		if (active == true) {
			// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
			img = app->tex->Load("Assets/UI/titlescreen.png");
			boton1 = app->tex->Load("Assets/UI/vsync.png");
			boton2 = app->tex->Load("Assets/UI/maximize.png");
			fondo = app->tex->Load("Assets/UI/options.png");
			patras = app->tex->Load("Assets/UI/cross.png");
			vol = app->tex->Load("Assets/UI/volumeup.png");
			novol = app->tex->Load("Assets/UI/novolume.png");
			intro = app->tex->Load("Assets/UI/introscreen.png");
			//Music is commented so that you can add your own music
			app->audio->PlayMusic("Assets/Audio/Music/soundtracktorrente.wav");
			buttonsound = app->audio->LoadFx("Assets/Audio/Fx/button.wav");
			

			//Get the size of the window
			app->win->GetWindowSize(windowW, windowH);

			//Get the size of the texture
			app->tex->GetSize(img, texW, texH);


			textPosX = (float)windowW / 2 - (float)texW / 2;
			textPosY = (float)windowH / 2 - (float)texH / 2;

			// Texture to highligh mouse position 
			mouseTileTex = app->tex->Load("Assets/Maps/tileSelection.png");

			// L15: DONE 2: Instantiate a new GuiControlButton in the Scene



			SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				app->map->mapData.width,
				app->map->mapData.height,
				app->map->mapData.tileWidth,
				app->map->mapData.tileHeight,
				app->map->mapData.tilesets.Count());


			//TITLE SCREEN
			SDL_Rect btPos = { windowW / 2 - 210  , windowH / 2 -115 ,410,80 };
			play = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos, this);
			play->state = GuiControlState::DISABLED;
			SDL_Rect btPos1 = { windowW / 2 - 210  , windowH / 2 - 115 +105 ,410,70 };
			options = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos1, this);
			options->state = GuiControlState::DISABLED;
			SDL_Rect btPos2 = { windowW / 2 - 210  , windowH / 2 - 115 +190 ,410,60 };
			exit = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos2, this);
			exit->state = GuiControlState::DISABLED;
			//OPTIONS
			SDL_Rect btPos3 = { windowW / 2 - 450  , windowH / 2 - 350 ,64,64 };
			back = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos3, this);
			back->state = GuiControlState::DISABLED;
			SDL_Rect btPos4 = { windowW / 2 - 100 + 64 , windowH / 2 - 200 + 5 ,200,50 };
			volume = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 1, "MyButton", btPos4, this);
			volume->state = GuiControlState::DISABLED;
			SDL_Rect btPos5 = { 412, 384,64,64 };
			vsync = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 1, "MyButton", btPos5, this);
			vsync->state = GuiControlState::DISABLED;
			
			SDL_Rect btPos6 = { 412, 284 ,64,64 };
			fullscreen = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 1, "MyButton", btPos6, this);
			fullscreen->state = GuiControlState::DISABLED;
		}

	
	return true;
}

// Called each loop iteration
bool Scene2::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Scene2::Update(float dt)
{

	if (active == true) {
		

		if (introdusion == false && play->state == GuiControlState::DISABLED && options->state == GuiControlState::DISABLED && exit->state == GuiControlState::DISABLED && back->state == GuiControlState::DISABLED) {
			play->state = GuiControlState::NORMAL;
			options->state = GuiControlState::NORMAL;
			exit->state = GuiControlState::NORMAL;
		}
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			introdusion = false;
		}
		app->scene->pause->state = GuiControlState::DISABLED;

		if (play->state == GuiControlState::PRESSED)
		{
			app->audio->PlayFx(buttonsound, 0);
			
			app->scene->active = true;
			app->map->active = true;
			app->physics->active = true;
			app->entityManager->active = true;
			play->state = GuiControlState::DISABLED;
			options->state = GuiControlState::DISABLED;
			exit->state = GuiControlState::DISABLED;
			app->win->scale = 3;
			app->scene->pause->state = GuiControlState::NORMAL;
			active = false;
		}
		if (options->state == GuiControlState::PRESSED) {
			app->audio->PlayFx(buttonsound, 0);
			pause = true;
			//QUITO LOS BOTONES 
			play->state = GuiControlState::DISABLED;
			options->state = GuiControlState::DISABLED;
			exit->state = GuiControlState::DISABLED;
			//MENU DE PAUSE
			back->state = GuiControlState::NORMAL;
			volume->state = GuiControlState::NORMAL;
			vsync->state = GuiControlState::NORMAL;
			fullscreen->state = GuiControlState::NORMAL;
		}
		if (vsync->state == GuiControlState::SELECTED) { 
			SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
			uint heigth;
			uint width;
			
			app->win->GetWindowSize(width, heigth);

			SDL_SetWindowFullscreen(app->win->window, 0);
			SDL_SetWindowSize(app->win->window, width, heigth);
		}
		if (fullscreen->state == GuiControlState::SELECTED) {
			app->maxFrameDuration = 1000 / 144;
		}
		if (exit->state == GuiControlState::PRESSED) {
			app->audio->PlayFx(buttonsound, 0);
			return false;
		}
		//MENU DE PAUSE BOTONES
		if (back->state == GuiControlState::PRESSED) {
			app->audio->PlayFx(buttonsound, 0);
			pause = false;
			//QUITO LOS BOTONES 
			play->state = GuiControlState::NORMAL;
			options->state = GuiControlState::NORMAL;
			exit->state = GuiControlState::NORMAL;
			//MENU DE PAUSE
			back->state = GuiControlState::DISABLED;
			volume->state = GuiControlState::DISABLED;
			vsync->state = GuiControlState::DISABLED;
			fullscreen->state = GuiControlState::DISABLED;
		}
		/*if (fullscreen.) {
			sdl_setwindowfullscreen(app->win->window, sdl_window_fullscreen);
		}*/

		app->render->DrawTexture(img,0,0);

		if (pause == true) {
			app->render->DrawTexture(fondo, 0, 0);
			app->render->DrawTexture(boton1, 412, 284);
			app->render->DrawTexture(boton2, 412, 384);
			app->render->DrawTexture(patras, 62, 34);
			if (volumen <= 0) {
				app->render->DrawTexture(novol, 412,184);
			}
			if (volumen > 0) {
				app->render->DrawTexture(vol, 412, 184);
			}
			}
		if(introdusion == true)
		app->render->DrawTexture(intro, 0, 0);
	}
	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	Mix_VolumeMusic(volumen);
	Mix_Volume(-1, volumen);

	return ret;
}

// Called before quitting
bool Scene2::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


bool Scene2::OnGuiMouseClickEvent(GuiControl* control)
{
	// L15: DONE 5: Implement the OnGuiMouseClickEvent method
	LOG("Press Gui Control: %d", control->id);

	return true;
}