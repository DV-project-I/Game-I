#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");	
	alma.PushBack({ 0, 0, 16, 16 });
	alma.PushBack({ 16, 0, 16, 16 });
	alma.PushBack({ 32, 0, 16, 16 });
	alma.PushBack({ 48, 0, 16, 16 });
	alma.PushBack({ 64, 0, 16, 16 });
	alma.PushBack({ 80, 0, 16, 16 });
	alma.speed = 0.2f;
	alma.loop = true;
}

Item::~Item() {}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentanim = &alma;
	
	return true;
}

bool Item::Start() {
	
	//initilize textures
	texture = app->tex->Load(texturePath);
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ITEM;
	
	return true;
}

bool Item::Update(float dt)
{
	 
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	currentanim = &alma;
	app->render->DrawTexture(texture, position.x, position.y +8, &currentanim->GetCurrentFrame());

	return true;
}

bool Item::CleanUp()
{
	return true;
}