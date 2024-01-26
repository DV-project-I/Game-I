#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Physics.h"
#include "Entity.h"
#include "../bat.h"
#include "Tree.h"
#include "Item.h"
#include "Boss.h"
#include "Galleta.h"

#include "GuiControl.h"
#include "GuiManager.h"
#include "Defs.h"
#include "Log.h"

#include "SDL_mixer/include/SDL_mixer.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	
		LOG("Loading Scene");
		bool ret = true;


		// iterate all objects in the scene
		// Check https://pugixml.org/docs/quickstart.html#access


		if (config.child("player")) {
			player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
			player->parameters = config.child("player");
		}

		if (config.child("galleta1")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta1");
		}
		if (config.child("galleta2")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta2");
		}
		if (config.child("galleta3")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta3");
		}
		if (config.child("galleta4")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta4");
		}
		if (config.child("galleta5")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta5");
		}
		if (config.child("galleta6")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta6");
		}
		if (config.child("galleta7")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta7");
		}
		if (config.child("galleta8")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta8");
		}
		if (config.child("galleta9")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta9");
		}
		if (config.child("galleta10")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta10");
		}
		if (config.child("galleta11")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta11");
		}
		if (config.child("galleta12")) {
			galleta = (Galleta*)app->entityManager->CreateEntity(EntityType::GALLETA);
			galleta->parameters = config.child("galleta12");
		}

		if (config.child("poty")) {
			poty = (Poty*)app->entityManager->CreateEntity(EntityType::POTION);
			poty->parameters = config.child("poty");
		}

		if (config.child("boss")) {
			boss = (Boss*)app->entityManager->CreateEntity(EntityType::BOSS);
			boss->parameters = config.child("boss");
		}


		if (config.child("enemy0")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy1");
		}

		if (config.child("enemy1")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy1");
		}

		if (config.child("enemy2")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy2");
		}

		if (config.child("enemy3")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy3");
		}

		if (config.child("enemy4")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy4");
		}

		if (config.child("enemy5")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy5");
		}

		if (config.child("enemy6")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy6");
		}

		if (config.child("enemy7")) {
			enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = config.child("enemy7");
		}

		if (config.child("bat0")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat0");
		}

		if (config.child("bat1")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat1");
		}


		if (config.child("bat2")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat2");
		}

		if (config.child("tree0")) {
			tree = (Tree*)app->entityManager->CreateEntity(EntityType::TREE);
			tree->parameters = config.child("tree0");
		}

		if (config.child("tree1")) {
			tree = (Tree*)app->entityManager->CreateEntity(EntityType::TREE);
			tree->parameters = config.child("tree1");
		}
		if (config.child("tree2")) {
			tree = (Tree*)app->entityManager->CreateEntity(EntityType::TREE);
			tree->parameters = config.child("tree2");
		}

		if (config.child("bat3")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat3");
		}

		if (config.child("tree3")) {
			tree = (Tree*)app->entityManager->CreateEntity(EntityType::TREE);
			tree->parameters = config.child("tree3");
		}

		if (config.child("bat4")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat4");
		}

		if (config.child("bat5")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat5");
		}

		if (config.child("tree4")) {
			tree = (Tree*)app->entityManager->CreateEntity(EntityType::TREE);
			tree->parameters = config.child("tree4");
		}

		if (config.child("bat6")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat6");
		}

		if (config.child("tree5")) {
			tree = (Tree*)app->entityManager->CreateEntity(EntityType::TREE);
			tree->parameters = config.child("tree5");
		}

		/*if (config.child("bat7")) {
			bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
			bat->parameters = config.child("bat7");
		}*/

		if (config.child("map")) {
			//Get the map name from the config file and assigns the value in the module
			app->map->name = config.child("map").attribute("name").as_string();
			app->map->path = config.child("map").attribute("path").as_string();
		}
		/*for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
		{
			Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
			item->parameters = itemNode;
		}*/
	
	
	
	
	return true;
}

// Called before the first frame
bool Scene::Start()
{

	
		// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
		img = app->tex->Load("Assets/UI/10hp.png");
		conf = app->tex->Load("Assets/UI/ajustes.png");
		boton1 = app->tex->Load("Assets/UI/vsync.png");
		boton2 = app->tex->Load("Assets/UI/maximize.png");
		fondo = app->tex->Load("Assets/UI/options.png");
		patras = app->tex->Load("Assets/UI/cross.png");
		vol = app->tex->Load("Assets/UI/volumeup.png");
		novol = app->tex->Load("Assets/UI/novolume.png");
		fuera = app->tex->Load("Assets/UI/exit.png");
		diescreen = app->tex->Load("Assets/UI/youlose.png");
		winscreen = app->tex->Load("Assets/UI/youwin.png");



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

		SDL_Rect btPos = { windowW / 2 + 400, windowH / 2 - 350 ,63,63 };
		pause = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos, this);
		pause->state = GuiControlState::NORMAL;
		//Menu de pausa
		SDL_Rect btPos3 = { windowW / 2 - 450  , windowH / 2 - 350 ,64,64 };
		back = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos3, this);
		back->state = GuiControlState::DISABLED;
		SDL_Rect btPos4 = { windowW / 2 - 100 +64 , windowH / 2 - 200 +5 ,200,50 };
		volume = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 1, "MyButton", btPos4, this);
		volume->state = GuiControlState::DISABLED;
		SDL_Rect btPos5 = { windowW / 2  -100 , windowH / 2 - 120 ,64,64 };
		vsync = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 1, "MyButton", btPos5, this);
		vsync->state = GuiControlState::DISABLED;
		SDL_Rect btPos6 = { windowW / 2  -100 , windowH / 2 - 21 ,64,64 };
		fullscreen = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 1, "MyButton", btPos6, this);
		fullscreen->state = GuiControlState::DISABLED;
		SDL_Rect btPos2 = { windowW / 2 - 450  , windowH / 2 + 270 ,64,64 };
		exit = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "MyButton", btPos2, this);
		exit->state = GuiControlState::DISABLED;
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// Renders the image in the center of the screen 
	if (active == true) {		
		
		float camSpeed = 0.25f;

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			app->render->camera.y -= (int)ceil(camSpeed * dt);

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			app->render->camera.y += (int)ceil(camSpeed * dt);

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			app->render->camera.x -= (int)ceil(camSpeed * dt);

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			app->render->camera.x += (int)ceil(camSpeed * dt);

		if (player->contadorcookies == 1) {
			cookies = app->tex->Load("Assets/Numeros/el1.png");
		}
		else if (player->contadorcookies == 2) {
			cookies = app->tex->Load("Assets/Numeros/el2.png");
		}
		else if (player->contadorcookies == 3) {
			cookies = app->tex->Load("Assets/Numeros/el3.png");
		}
		else if (player->contadorcookies == 4) {
			cookies = app->tex->Load("Assets/Numeros/el4.png");
		}
		else if (player->contadorcookies == 5) {
			cookies = app->tex->Load("Assets/Numeros/el5.png");
		}
		else if (player->contadorcookies == 6) {
			cookies = app->tex->Load("Assets/Numeros/el6.png");
		}
		else if (player->contadorcookies == 7) {
			cookies = app->tex->Load("Assets/Numeros/el7.png");
		}
		else if (player->contadorcookies == 8) {
			cookies = app->tex->Load("Assets/Numeros/el8.png");
		}
		else if (player->contadorcookies == 9) {
			cookies = app->tex->Load("Assets/Numeros/el9.png");
		}
		else if (player->contadorcookies == 10) {
			cookies = app->tex->Load("Assets/Numeros/el10.png");
		}
		else if (player->contadorcookies == 11) {
			cookies = app->tex->Load("Assets/Numeros/el11.png");
		}
		else if (player->contadorcookies == 12) {
			cookies = app->tex->Load("Assets/Numeros/el12.png");
		}
		else if (player->contadorcookies == 13) {
			cookies = app->tex->Load("Assets/Numeros/el13.png");
		}
		else if (player->contadorcookies == 14) {
			cookies = app->tex->Load("Assets/Numeros/el14.png");
		}
		else if (player->contadorcookies == 15) {
			cookies = app->tex->Load("Assets/Numeros/el15.png");
		}
		else if (player->contadorcookies == 16) {
			cookies = app->tex->Load("Assets/Numeros/el16.png");
		}
		else if (player->contadorcookies == 17) {
			cookies = app->tex->Load("Assets/Numeros/el17.png");
		}
		else if (player->contadorcookies == 18) {
			cookies = app->tex->Load("Assets/Numeros/el18.png");
		}
		else if (player->contadorcookies == 19) {
			cookies = app->tex->Load("Assets/Numeros/el19.png");
		}
		else if (player->contadorcookies == 20) {
			cookies = app->tex->Load("Assets/Numeros/el20.png");
		}
		else if (player->contadorcookies == 21) {
			cookies = app->tex->Load("Assets/Numeros/el21.png");
		}
		else if (player->contadorcookies == 22) {
			cookies = app->tex->Load("Assets/Numeros/el22.png");
		}
		else if (player->contadorcookies == 23) {
			cookies = app->tex->Load("Assets/Numeros/el23.png");
		}
		else if (player->contadorcookies == 24) {
			cookies = app->tex->Load("Assets/Numeros/el24.png");
		}
		else if (player->contadorcookies == 25) {
			cookies = app->tex->Load("Assets/Numeros/el25.png");
		}
		else if (player->contadorcookies == 26) {
			cookies = app->tex->Load("Assets/Numeros/el26.png");
		}
		else if (player->contadorcookies == 27) {
			cookies = app->tex->Load("Assets/Numeros/el27.png");
		}
		else if (player->contadorcookies == 28) {
			cookies = app->tex->Load("Assets/Numeros/el28.png");
		}
		else if (player->contadorcookies == 29) {
			cookies = app->tex->Load("Assets/Numeros/el29.png");
		}
		else if (player->contadorcookies == 30) {
			cookies = app->tex->Load("Assets/Numeros/el30.png");
		}
		else if (player->contadorcookies == 31) {
			cookies = app->tex->Load("Assets/Numeros/el31.png");
		}
		else if (player->contadorcookies == 32) {
			cookies = app->tex->Load("Assets/Numeros/el32.png");
		}
		else if (player->contadorcookies == 33) {
			cookies = app->tex->Load("Assets/Numeros/el33.png");
		}
		else if (player->contadorcookies == 34) {
			cookies = app->tex->Load("Assets/Numeros/el34.png");
		}
		else if (player->contadorcookies == 35) {
		cookies = app->tex->Load("Assets/Numeros/el35.png");
		}
		else if (player->contadorcookies == 36) {
		cookies = app->tex->Load("Assets/Numeros/el36.png");
		}
		else if (player->contadorcookies == 37) {
		cookies = app->tex->Load("Assets/Numeros/el37.png");
		}
		else if (player->contadorcookies == 38) {
		cookies = app->tex->Load("Assets/Numeros/el38.png");
		}
		else if (player->contadorcookies == 39) {
		cookies = app->tex->Load("Assets/Numeros/el39.png");
		}
		else if (player->contadorcookies == 40) {
		cookies = app->tex->Load("Assets/Numeros/el40.png");
		}
		else if (player->contadorcookies == 41) {
		cookies = app->tex->Load("Assets/Numeros/el41.png");
		}
		else if (player->contadorcookies == 42) {
		cookies = app->tex->Load("Assets/Numeros/el42.png");
		}
		else if (player->contadorcookies == 43) {
		cookies = app->tex->Load("Assets/Numeros/el43.png");
		}
		else if (player->contadorcookies == 44) {
		cookies = app->tex->Load("Assets/Numeros/el44.png");
		}
		else if (player->contadorcookies == 45) {
		cookies = app->tex->Load("Assets/Numeros/el45.png");
		}
		else if (player->contadorcookies == 46) {
		cookies = app->tex->Load("Assets/Numeros/el46.png");
		}
		else if (player->contadorcookies == 47) {
		cookies = app->tex->Load("Assets/Numeros/el47.png");
		}
		else if (player->contadorcookies == 48) {
		cookies = app->tex->Load("Assets/Numeros/el48.png");
		}
		else if (player->contadorcookies == 49) {
		cookies = app->tex->Load("Assets/Numeros/el49.png");
		}
		else if (player->contadorcookies == 50) {
		cookies = app->tex->Load("Assets/Numeros/el50.png");
		}
		if (player->hp == 10) {
			img = app->tex->Load("Assets/UI/10hp.png");
		}
		else if (player->hp == 9) {
			img = app->tex->Load("Assets/UI/9hp.png");
		}
		else if (player->hp == 8) {
			img = app->tex->Load("Assets/UI/8hp.png");
		}
		else if (player->hp == 7) {
			img = app->tex->Load("Assets/UI/7hp.png");
		}
		else if (player->hp == 6) {
			img = app->tex->Load("Assets/UI/6hp.png");
		}
		else if (player->hp == 5) {
			img = app->tex->Load("Assets/UI/5hp.png");
		}
		else if (player->hp == 4) {
			img = app->tex->Load("Assets/UI/4hp.png");
		}
		else if (player->hp == 3) {
			img = app->tex->Load("Assets/UI/3hp.png");
		}
		else if (player->hp == 2) {
			img = app->tex->Load("Assets/UI/2hp.png");
		}
		else if (player->hp == 1) {
			img = app->tex->Load("Assets/UI/1hp.png");
		}


		app->render->camera.x = (-player->position.x) * app->win->GetScale() + 512;
		app->render->camera.y = (-player->position.y) * app->win->GetScale() + 384 +100;

		
		

		//------------------MENU DE PAUSE-----------------------------
		
		if (pause->state == GuiControlState::PRESSED) {
			onpause = true;
			
		}
		if (back->state == GuiControlState::PRESSED) {
			onpause = false;
			app->win->scale = 3;
			pause->state = GuiControlState::NORMAL;
			app->physics->active = true;
			app->entityManager->active = true;
			back->state = GuiControlState::DISABLED;
			volume->state = GuiControlState::DISABLED;
			vsync->state = GuiControlState::DISABLED;
			fullscreen->state = GuiControlState::DISABLED;
			exit->state = GuiControlState::DISABLED;
		}
		if (exit->state == GuiControlState::PRESSED) {
			return false;
		}

		if (onpause == true) {
			pause->state = GuiControlState::DISABLED;
			app->physics->active = false;
			app->entityManager->active = false;
			back->state = GuiControlState::NORMAL;
			volume->state = GuiControlState::NORMAL;
			vsync->state = GuiControlState::NORMAL;
			fullscreen->state = GuiControlState::NORMAL;
			exit->state = GuiControlState::NORMAL;
			app->win->scale = 1;
			app->render->DrawTexture(fondo, player->position.x - 512, player->position.y - 383 - 100);
			app->render->DrawTexture(boton1, player->position.x -100, player->position.y - 120 - 100);
			app->render->DrawTexture(boton2, player->position.x -100, player->position.y - 20 - 100);
			app->render->DrawTexture(patras, player->position.x - 450, player->position.y -350 - 100);
			if (volumen <= 0) {
			app->render->DrawTexture(novol, player->position.x - 100, player->position.y - 200 - 100);
			}
			if (volumen > 0) {
				app->render->DrawTexture(vol, player->position.x - 100, player->position.y - 200 - 100);
			}
			app->render->DrawTexture(fuera, player->position.x - 450, player->position.y + 270 - 100);
		}
		if (onpause == false) {
			if (app->win->scale == 3) {
			app->render->DrawTexture(conf, player->position.x + 133, player->position.y -117 - 33);
			app->render->DrawTexture(img, player->position.x - 160, player->position.y - 120 - 33);
			app->render->DrawTexture(cookies, player->position.x - 100, player->position.y - 120 - 33);
			}
			else if (app->win->scale == 2) {
				app->render->DrawTexture(conf, player->position.x + 133 +66, player->position.y - 117 - 109);
				app->render->DrawTexture(img, player->position.x - 160 -66, player->position.y - 120 - 66);
				app->render->DrawTexture(cookies, player->position.x - 100 - 66, player->position.y - 120 - 66);
			}
			
		}
		//------------------NO MENU DE PAUSE-----------------------------
		
		if (player->vidas <= 0) {
			app->physics->active = false;
			app->entityManager->active = false;
			pause->state = GuiControlState::DISABLED;
			app->win->scale = 1;
			app->render->DrawTexture(diescreen, player->position.x - 512, player->position.y - 383 - 100);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				return false;
		}
		if (boss->ganaste == true) {
			app->physics->active = false;
			app->entityManager->active = false;
			pause->state = GuiControlState::DISABLED;
			app->win->scale = 1;
			app->render->DrawTexture(winscreen, player->position.x - 512, player->position.y - 383 - 100);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				return false;
		}
		

		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) app->SaveRequest();
		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) app->LoadRequest();
	}
	
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		onpause = true;

	//volume sounds
	Mix_VolumeMusic(volumen);
	Mix_Volume(-1, volumen);

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

iPoint Scene::GetPLayerPosition() {
	return player->position;
}
bool Scene::LoadState(pugi::xml_node node) {

	int x = node.child("player").attribute("x").as_int();
	int y = node.child("player").attribute("y").as_int();
	b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	player->SetPosition(x, y); 

	int xe = node.child("enemy").attribute("x").as_int();
	int ye = node.child("enemy").attribute("y").as_int();
	
	enemy->SetPosition(xe, ye);

	int xb = node.child("bat").attribute("x").as_int();
	int yb = node.child("bat").attribute("y").as_int();
	
	bat->SetPosition(xb, yb);

	return true;
}



bool Scene::SaveState(pugi::xml_node node) {

	pugi::xml_node PlayerPos = node.append_child("player");
	PlayerPos.append_attribute("x").set_value(app->scene->player->position.x);
	PlayerPos.append_attribute("y").set_value(player->position.y);

	pugi::xml_node EnemyPos = node.append_child("enemy");
	EnemyPos.append_attribute("x").set_value(app->scene->enemy->position.x);
	EnemyPos.append_attribute("y").set_value(enemy->position.y);

	pugi::xml_node BatPos = node.append_child("bat");
	BatPos.append_attribute("x").set_value(app->scene->bat->position.x);
	BatPos.append_attribute("y").set_value(bat->position.y);
		

	return true;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	// L15: DONE 5: Implement the OnGuiMouseClickEvent method
	LOG("Press Gui Control: %d", control->id);

	return true;
}