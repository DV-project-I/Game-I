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
	WalkAnimIzq.speed = 0.3f;
	WalkAnimIzq.loop = true;

	WalkAnimDer.PushBack({ 175, 25, 25, 25 });
	WalkAnimDer.PushBack({ 150, 25, 25, 25 });
	WalkAnimDer.PushBack({ 125, 25, 25, 25 });	
	WalkAnimDer.PushBack({ 100, 25, 25, 25 });
	WalkAnimDer.PushBack({ 75, 25, 25, 25 });
	WalkAnimDer.PushBack({ 50, 25, 25, 25 });	
	WalkAnimDer.PushBack({ 25, 25, 25, 25 });
	WalkAnimDer.PushBack({ 0, 25, 25, 25 });
	WalkAnimDer.speed = 0.3f;
	WalkAnimDer.loop = true;
	
	IdleAnimDer.PushBack({ 150, 100, 25, 25 });
	IdleAnimDer.speed = 0.3f;
	IdleAnimDer.loop = true;
	IdleAnimIzq.PushBack({ 175, 100, 25, 25 });
	IdleAnimIzq.speed = 0.3f;
	IdleAnimIzq.loop = true;

	AtackAnimIzq.PushBack({ 0, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 25, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 50, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 75, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 100, 50, 25, 25 });	
	AtackAnimIzq.PushBack({ 125, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 150, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 175, 50, 25, 25 });
	AtackAnimIzq.speed = 0.3f;
	AtackAnimIzq.loop = false;

	AtackAnimDer.PushBack({ 175, 75, 25, 25 });
	AtackAnimDer.PushBack({ 150, 75, 25, 25 });
	AtackAnimDer.PushBack({ 125, 75, 25, 25 });
	AtackAnimDer.PushBack({ 100, 75, 25, 25 });	
	AtackAnimDer.PushBack({ 75, 75, 25, 25 });	
	AtackAnimDer.PushBack({ 50, 75, 25, 25 });
	AtackAnimDer.PushBack({ 25, 75, 25, 25 });
	AtackAnimDer.PushBack({ 0,  75, 25, 25 });
	AtackAnimDer.speed = 0.3f;
	AtackAnimDer.loop = false;

	DeathAnim.PushBack({ 0, 100, 25, 25 });
	DeathAnim.PushBack({ 25, 100, 25, 25 });
	DeathAnim.PushBack({ 50, 100, 25, 25 });
	DeathAnim.PushBack({ 75, 100, 30, 25 });
	DeathAnim.PushBack({ 105, 100, 25, 25 });
	DeathAnim.speed = 0.3f;
	DeathAnim.loop = false;
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
	camino = app->tex->Load("Assets/Textures/camino.png");
	torrentesound = app->audio->LoadFx("Assets/Audio/Fx/torrente.wav");
	torrentesound2 = app->audio->LoadFx("Assets/Audio/Fx/punchtorrente.wav");
	
	

	hp = 10;
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	
	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");


	return true;
}


bool Enemy::Update(float dt) {
	movX = 0;
	b2Vec2 vel;
	vel.y = -GRAVITY_Y - 25.2f;

	if (app->scene->player->IsDeath == true) {
		IsDeath = false;	
	}

	if (IsDeath == true) {
		currentAnimation = &DeathAnim;
		pbody->ctype = ColliderType::ITEM;
		movX = 0;
		movY = 0;

	}
	else {
		

		iPoint origin = iPoint(this->position.x, this->position.y);
		iPoint origin2 = iPoint(app->scene->player->position.x, app->scene->player->position.y);


		if (position.DistanceTo(app->scene->player->position) < 120) {


			if (position.DistanceTo(app->scene->player->position) < 150 && timertoplay > 500) {

				app->audio->PlayFx(torrentesound, 0);
				timertoplay = 0;

			}
			timertoplay++;

			//COSAS DEL PATHFINDING
			app->map->pathfinding->CreatePath(app->map->WorldToMap(origin.x, origin.y), app->map->WorldToMap(origin2.x, origin2.y));
			// DIBUJAR EL PATH

			if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
				pathmode = !pathmode;
			}

		}

		

			const DynArray<iPoint>* path = app->map->pathfinding->GetLastPath();
			for (uint i = 0; i < path->Count(); ++i)
			{
				
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				if (pathmode == true) {
					app->render->DrawTexture(camino, pos.x, pos.y);
				}
				movX = (pos.x - this->position.x) / 25;
				vel.x = movX;

			}
		
	
		
		if (vel.x < 0) {
			currentAnimation = &WalkAnimIzq;
		}
		else	if (vel.x > 0) {
			currentAnimation = &WalkAnimDer;
		}
		else	if (vel.y == 0 && vel.x == 0 && currentAnimation == &WalkAnimIzq) {
			currentAnimation = &IdleAnimIzq;
		}
		else if (vel.y == 0 && vel.x == 0 && currentAnimation == &WalkAnimDer) {
			currentAnimation = &IdleAnimDer;
		}

		if (position.DistanceTo(app->scene->player->position) < 50 && currentAnimation == &WalkAnimDer) {
			
			currentAnimation = &AtackAnimDer;
			app->audio->PlayFx(torrentesound2, 0);
			
			if (AtackAnimDer.HasFinished()) {
				AtackAnimDer.Reset();
				Ataca = false;
			}

		}
		if (position.DistanceTo(app->scene->player->position) < 50 && currentAnimation == &WalkAnimIzq) {
			currentAnimation = &AtackAnimIzq;
			app->audio->PlayFx(torrentesound2, 0);

			if (AtackAnimIzq.HasFinished()) {
				AtackAnimIzq.Reset();
				Ataca = false;
			}

		}
	}

	vel.x = movX;

	currentAnimation->Update();

	pbody->body->SetLinearVelocity(vel);

	this->position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	this->position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	

	app->render->DrawTexture(texture, position.x +3 , position.y, &currentAnimation->GetCurrentFrame());
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
		IsDeath = true;
		LOG("Collision INSTAKILL");
		break;
	case ColliderType::PLAYERATTACK:
		IsDeath = true;
		LOG("Collision PLAYERATTACK");
		break;
	}


}
void Enemy::SetPosition(int x, int y) {
	DeathAnim.Reset();
	position.x = x;
	position.y = y;
	b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	pbody->body->SetTransform(newPos, pbody->body->GetAngle());

	IsDeath = false;

}

void Enemy::EnemyDeath()
{
	currentAnimation = &DeathAnim;
	if (currentAnimation->HasFinished() == true) {
		SetPosition(parameters.attribute("x").as_int(), parameters.attribute("y").as_int());
	}

}
