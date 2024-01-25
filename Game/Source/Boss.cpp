#include "Boss.h"
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
#include "Bullet.h"
Boss::Boss() : Entity(EntityType::BOSS)
{
	name.Create("boss");
	WalkAnimIzq.PushBack({ 0, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 25, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 50, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 75, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 100, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 125, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 150, 0, 25, 25 });
	WalkAnimIzq.PushBack({ 175, 0, 25, 25 });
	WalkAnimIzq.speed = 0.1f;
	WalkAnimIzq.loop = true;

	WalkAnimDer.PushBack({ 175, 25, 25, 25 });
	WalkAnimDer.PushBack({ 150, 25, 25, 25 });
	WalkAnimDer.PushBack({ 125, 25, 25, 25 });	
	WalkAnimDer.PushBack({ 100, 25, 25, 25 });
	WalkAnimDer.PushBack({ 75, 25, 25, 25 });
	WalkAnimDer.PushBack({ 50, 25, 25, 25 });	
	WalkAnimDer.PushBack({ 25, 25, 25, 25 });
	WalkAnimDer.PushBack({ 0, 25, 25, 25 });
	WalkAnimDer.speed = 0.1f;
	WalkAnimDer.loop = true;

	AtackAnimIzq.PushBack({ 0, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 25, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 50, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 75, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 100, 50, 25, 25 });	
	AtackAnimIzq.PushBack({ 125, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 150, 50, 25, 25 });
	AtackAnimIzq.PushBack({ 175, 50, 25, 25 });
	AtackAnimIzq.speed = 0.3f;
	AtackAnimIzq.loop = true;

	AtackAnimDer.PushBack({ 175, 75, 25, 25 });
	AtackAnimDer.PushBack({ 150, 75, 25, 25 });
	AtackAnimDer.PushBack({ 125, 75, 25, 25 });
	AtackAnimDer.PushBack({ 100, 75, 25, 25 });	
	AtackAnimDer.PushBack({ 75, 75, 25, 25 });	
	AtackAnimDer.PushBack({ 50, 75, 25, 25 });
	AtackAnimDer.PushBack({ 25, 75, 25, 25 });
	AtackAnimDer.PushBack({ 0,  75, 25, 25 });
	AtackAnimDer.speed = 0.3f;
	AtackAnimDer.loop = true;

	DeathAnim.PushBack({ 0, 100, 25, 25 });
	DeathAnim.PushBack({ 25, 100, 25, 25 });
	DeathAnim.PushBack({ 50, 100, 25, 25 });
	DeathAnim.PushBack({ 75, 100, 30, 25 });
	DeathAnim.PushBack({ 105, 100, 25, 25 });
	DeathAnim.speed = 0.3f;
	DeathAnim.loop = false;
}

Boss::~Boss() {

}

bool Boss::Awake() {


	
PathFinding path;
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentAnimation = &IdleAnimDer;

	return true;
}

bool Boss::Start() {

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

	ataque = app->physics->CreateRectangle(0, 0, 30, 10, bodyType::STATIC);
	ataque->ctype = ColliderType::ENEMY;
	ataque->body->GetFixtureList()->SetSensor(true);
	
	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");


	return true;
}


bool Boss::Update(float dt) {
	movX = 0;

	b2Vec2 vel;
	vel.y = -GRAVITY_Y - 25.2f;

	if (app->scene->player->IsDeath == true) {
		IsDeath = false;
		pbody->ctype = ColliderType::ENEMY;
	}

	if (IsDeath == true) {
		currentAnimation = &DeathAnim;
		pbody->ctype = ColliderType::ITEM;
		movX = 0;
		movY = 0;
		ganaste = true;

	}
	else {
		
		if (phase2 == false) {


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

		}

		if (phase2 == true) {
			//app->entityManager->CreateEntity();
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
	}
		//Ataque
		if (position.DistanceTo(app->scene->player->position) < 50 && currentAnimation == &WalkAnimDer) {
			
			currentAnimation = &AtackAnimDer;
			app->audio->PlayFx(torrentesound2, 0);
			
			if (cooldown > 60) {
				int x = position.x + 30;
				int y = position.y + 15;
				b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
				ataque->body->SetTransform(newPos, ataque->body->GetAngle());
				
			}

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
	
	if (position.DistanceTo(app->scene->player->position) > 50)
	{
		b2Vec2 ResetPos(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
		ataque->body->SetTransform(ResetPos, ataque->body->GetAngle());
		timerataque = 0;

	}
	
	vel.x = movX;
	if (punch == true && currentAnimation == &WalkAnimDer || punch == true && currentAnimation == &AtackAnimDer) {
		vel.x = -PUNCHVELOCITY;
		punch = false;
	}
	if (punch == true && currentAnimation == &WalkAnimIzq || punch == true && currentAnimation == &AtackAnimIzq) {
		vel.x = PUNCHVELOCITY;
		punch = false;
	}
	currentAnimation->Update();

	pbody->body->SetLinearVelocity(vel);

	if (hp <= 0) {
		IsDeath = true;
	}

	this->position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	this->position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	
	timerataque++;
	cooldown++;

	app->render->DrawTexture(texture, position.x +3 , position.y, &currentAnimation->GetCurrentFrame());
	return true;
}

bool Boss::CleanUp() {
	return true;
}

void Boss::OnCollision(PhysBody* physA, PhysBody* physB) {
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
		punch = true;
		phase2 = !phase2;
		hp--;
		LOG("Collision PLAYERATTACK");
		break;
	}


}
void Boss::SetPosition(int x, int y) {
	DeathAnim.Reset();
	position.x = x;
	position.y = y;
	b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	pbody->body->SetTransform(newPos, pbody->body->GetAngle());

	IsDeath = false;

}

void Boss::EnemyDeath()
{
	currentAnimation = &DeathAnim;

	if (currentAnimation->HasFinished() == true) {
		SetPosition(parameters.attribute("x").as_int(), parameters.attribute("y").as_int());
	}

}
