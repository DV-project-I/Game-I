#include "Bat.h"
#include "../App.h"
#include "../Textures.h"
#include "../Audio.h"
#include "../Input.h"
#include "../Render.h"
#include "../Scene.h"
#include "../Log.h"
#include "../Point.h"
#include "../Physics.h"
#include "../Animation.h"
#include "../Pathfinding.h"
#include "../Player.h"
#include "../Map.h"
#include "../Entity.h"


Bat::Bat() : Entity(EntityType::BAT)
{
	name.Create("bat");
	Batfly.PushBack({ 0, 160, 32, 32 });
	Batfly.PushBack({ 32, 160, 32, 32 });
	Batfly.PushBack({ 64, 160, 32, 32 });
	Batfly.PushBack({ 96, 160, 32, 32 });
	Batfly.speed = 0.1f;
	Batfly.loop = true;

	DeathBat.PushBack({ 0, 192, 32, 32 });
	DeathBat.PushBack({ 32, 192, 32, 32 });
	DeathBat.PushBack({ 64, 192, 32, 32 });
	DeathBat.PushBack({ 96, 192, 32, 32 });
	DeathBat.speed = 0.1f;
	DeathBat.loop = false;
}

Bat::~Bat() {

}

bool Bat::Awake() {

	PathFinding path;
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentAnimation = &Batfly;

	return true;
}

bool Bat::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	camino = app->tex->Load("Assets/Textures/camino.png");

	batsound = app->audio->LoadFx("Assets/Audio/Fx/flying.wav");




	
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	AreaVision.h = 50;
	AreaVision.w = 100;
	AreaVision.x = position.x - (AreaVision.w / 2);
	AreaVision.y = position.y - (AreaVision.h / 2);

	return true;
}


bool Bat::Update(float dt) {

	b2Vec2 vel;
	movX = 0;
	movY = 0;

		if (app->scene->player->IsDeath == true) {
		IsDeath = false;
	}

	if (IsDeath == true) {
		currentAnimation = &DeathBat;
		movX = 0;
		movY = -GRAVITY_Y + 25.2f;
		pbody->ctype = ColliderType::ITEM;

	}
	else {


		iPoint origin = iPoint(this->position.x, this->position.y);
		iPoint origin2 = iPoint(app->scene->player->position.x, app->scene->player->position.y);

		if (position.DistanceTo(app->scene->player->position) < 150) {


			if (position.DistanceTo(app->scene->player->position) < 150 && timertoplay > 80) {

				app->audio->PlayFx(batsound, 0);
				timertoplay = 0;

			}
			timertoplay++;

			

			app->map->pathfinding->CreatePath(app->map->WorldToMap(origin.x, origin.y), app->map->WorldToMap(origin2.x, origin2.y));
			// DIBUJAR EL PATH
			const DynArray<iPoint>* path = app->map->pathfinding->GetLastPath();
			for (uint i = 0; i < path->Count(); ++i)
			{

				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				app->render->DrawTexture(camino, pos.x, pos.y);

				movX = (pos.x - this->position.x) / 30;
				vel.x = movX;

				movY = (pos.y - this->position.y) / 30;
				vel.y = movY;

				if (pos.x - this->position.x < 20) {
					Ataca = true;
				}
			}




		}
		currentAnimation = &Batfly;
	}
	

	vel.x = movX;
	vel.y = movY;

	currentAnimation->Update();

	pbody->body->SetLinearVelocity(vel);

	this->position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	this->position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;


	app->render->DrawTexture(texture, position.x + 3, position.y -5, &currentAnimation->GetCurrentFrame());
	return true;


}

bool Bat::CleanUp() {
	return true;
}

void Bat::OnCollision(PhysBody* physA, PhysBody* physB) {
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
	case ColliderType::PLAYERATTACK:
		IsDeath = true;
		LOG("Collision PLAYERATTACK");
		break;
	}
	}

void Bat::SetPosition(int x, int y) {
	position.x = x;
	position.y = y;
	b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	pbody->body->SetTransform(newPos, pbody->body->GetAngle());

	IsDeath = false;

}

void Bat::BatDeath()
{
	Batfly.loop = false;
	

}



