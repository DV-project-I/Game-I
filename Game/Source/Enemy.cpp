#include "Enemy.h"
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
#include "Pathfinding.h"
#include "Player.h"
#include "Map.h"
#include "Entity.h"

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("enemy");
	WalkAnimIzq.PushBack({ 0, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 25, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 50, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 75, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 100, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 125, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 150, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 175, 0, 25, 25 });
	
}

Enemy::~Enemy() {

}

bool Enemy::Awake() {


	
PathFinding path;
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentAnimation = &IdleAnimDer;

	return true;
}

bool Enemy::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	camino = app->tex->Load("../Assets/Textures/camino.png");
	
	

	hp = 10;
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");


	return true;
}


bool Enemy::Update(float dt) {

	b2Vec2 vel;
	vel.y = -GRAVITY_Y;

	iPoint origin = iPoint(this->position.x, this->position.y);
	iPoint origin2 = iPoint(app->scene->player->position.x, app->scene->player->position.y);


	//If mouse button is pressed modify player position
	

	app->map->pathfinding->CreatePath(app->map->WorldToMap(origin.x, origin.y), app->map->WorldToMap(origin2.x, origin2.y));
	

	// L13: Get the latest calculated path and draw
	const DynArray<iPoint>* path = app->map->pathfinding->GetLastPath();
	for (uint i = 0; i < path->Count(); ++i)
	{
		
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(camino, pos.x, pos.y);

		movX = (pos.x - this->position.x)/50;
		vel.x = movX;
	}

	

	pbody->body->SetLinearVelocity(vel);

	this->position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	this->position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	

	app->render->DrawTexture(texture, position.x +3 , position.y);
	return true;
}

bool Enemy::CleanUp() {
	return true;
}

void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {
	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		//app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	case ColliderType::INSTAKILL:
		
		LOG("Collision INSTAKILL");
		break;
	}


}
