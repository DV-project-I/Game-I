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
		//Music is commented so that you can add your own music
		app->audio->PlayMusic("Assets/Audio/Music/soundtracktorrente.wav");

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

		

		SDL_Rect btPos = { windowW / 2 -90  , windowH / 2 ,180,80 };
		play = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos, this);
		SDL_Rect btPos1 = { windowW / 2 - 90  , windowH / 2 +90 ,180,80 };
		options = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos1, this);
		SDL_Rect btPos2 = { windowW / 2 - 90  , windowH / 2 +180 ,180,80 };
		exit = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos2, this);
		
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

	app->render->DrawTexture(img, windowW, windowH);
	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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