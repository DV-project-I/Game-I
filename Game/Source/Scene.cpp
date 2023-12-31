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

#include "Defs.h"
#include "Log.h"

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

	if (config.child("enemy0")) {
		enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = config.child("enemy0");
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

	if (config.child("enemy1")) {
		enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = config.child("enemy1");
	}
	if (config.child("enemy2")) {
		enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = config.child("enemy2");
	}

	if (config.child("bat3")) {
		bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
		bat->parameters = config.child("bat3");
	}

	if (config.child("enemy3")) {
		enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = config.child("enemy3");
	}

	if (config.child("bat4")) {
		bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
		bat->parameters = config.child("bat4");
	}

	if (config.child("bat5")) {
		bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
		bat->parameters = config.child("bat5");
	}

	if (config.child("enemy4")) {
		enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = config.child("enemy4");
	}

	if (config.child("bat6")) {
		bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
		bat->parameters = config.child("bat6");
	}

	if (config.child("enemy5")) {
		enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = config.child("enemy5");
	}

	if (config.child("bat7")) {
		bat = (Bat*)app->entityManager->CreateEntity(EntityType::BAT);
		bat->parameters = config.child("bat7");
	}

	if (config.child("map")) {
		//Get the map name from the config file and assigns the value in the module
		app->map->name = config.child("map").attribute("name").as_string();
		app->map->path = config.child("map").attribute("path").as_string();
	}

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	img = app->tex->Load("Assets/UI/10hp.png");
	
	//Music is commented so that you can add your own music
	app->audio->PlayMusic("Assets/Audio/Music/soundtracktorrente.wav");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(img, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width,
		app->map->mapData.height,
		app->map->mapData.tileWidth,
		app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());


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

	float camSpeed = 0.25f; 

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= (int)ceil(camSpeed * dt);

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += (int)ceil(camSpeed * dt);

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= (int)ceil(camSpeed * dt);

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += (int)ceil(camSpeed * dt);
	
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
	
	app->render->camera.x = (-player->position.x)* app->win->GetScale() +512; 
	app->render->camera.y = (-player->position.y)* app->win->GetScale() + 384;
	
	app->render->DrawTexture(img, player->position.x -160, player->position.y -120);

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) app->SaveRequest();
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) app->LoadRequest();
	
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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