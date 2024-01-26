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
	WalkAnimIzq.PushBack({ 0, 0, 64, 64 });
	WalkAnimIzq.PushBack({ 64, 0, 64, 64 });
	WalkAnimIzq.PushBack({ 128, 0, 64, 64 });
	WalkAnimIzq.PushBack({ 192, 0, 64, 64 });

	WalkAnimIzq.speed = 0.1f;
	WalkAnimIzq.loop = true;

	WalkAnimDer.PushBack({ 0, 64, 64, 64 });
	WalkAnimDer.PushBack({ 64, 64, 64, 64 });
	WalkAnimDer.PushBack({ 128, 64, 64, 64 });
	WalkAnimDer.PushBack({ 192, 64, 64, 64 });

	WalkAnimDer.speed = 0.1f;
	WalkAnimDer.loop = true;

	AtackAnimIzq.PushBack({ 0, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 64, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 128, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 192, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 256, 128, 64, 64 });	
	AtackAnimIzq.PushBack({ 320, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 384, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 448, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 512, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 576, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 640, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 704, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 768, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 832, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 896, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 960, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 1024, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 1088, 128, 64, 64 });
	AtackAnimIzq.PushBack({ 1152, 128, 64, 64 });
	AtackAnimIzq.speed = 0.3f;
	AtackAnimIzq.loop = true;

	AtackAnimDer.PushBack({ 0, 192, 64, 64 });
	AtackAnimDer.PushBack({ 64, 192, 64, 64 });
	AtackAnimDer.PushBack({ 128, 192, 64, 64 });
	AtackAnimDer.PushBack({ 192, 192, 64, 64 });
	AtackAnimDer.PushBack({ 256, 192, 64, 64 });
	AtackAnimDer.PushBack({ 320, 192, 64, 64 });
	AtackAnimDer.PushBack({ 384, 192, 64, 64 });
	AtackAnimDer.PushBack({ 448, 192, 64, 64 });
	AtackAnimDer.PushBack({ 512, 192, 64, 64 });
	AtackAnimDer.PushBack({ 576, 192, 64, 64 });
	AtackAnimDer.PushBack({ 640, 192, 64, 64 });
	AtackAnimDer.PushBack({ 704, 192, 64, 64 });
	AtackAnimDer.PushBack({ 768, 192, 64, 64 });
	AtackAnimDer.PushBack({ 832, 192, 64, 64 });
	AtackAnimDer.PushBack({ 896, 192, 64, 64 });
	AtackAnimDer.PushBack({ 960, 192, 64, 64 });
	AtackAnimDer.PushBack({ 1024, 192, 64, 64 });
	AtackAnimDer.PushBack({ 1088, 192, 64, 64 });
	AtackAnimDer.PushBack({ 1152, 192, 64, 64 });
	AtackAnimDer.speed = 0.3f;
	AtackAnimDer.loop = true;

	DesaparecerAnim.PushBack({ 0, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 64, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 128, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 192, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 256, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 320, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 384, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 448, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 512, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 576, 256, 64, 64 });
	DesaparecerAnim.PushBack({ 640, 256, 64, 64 });
	DesaparecerAnim.speed = 0.2f;
	DesaparecerAnim.loop = false;

	DeathAnim.PushBack({ 0, 100, 64, 64 });
	DeathAnim.PushBack({ 25, 100, 64, 64 });
	DeathAnim.PushBack({ 50, 100, 64, 64 });
	DeathAnim.PushBack({ 75, 100, 64, 64 });
	DeathAnim.PushBack({ 105, 100, 64, 64 });
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
	torrentesound2 = app->audio->LoadFx("Assets/Audio/Fx/ataquemeleboss.wav");

	
	
	hp = 10;
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x +10, position.y, 15, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	ataque = app->physics->CreateRectangle(0, 0, 32, 64, bodyType::STATIC);
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
		
		


			iPoint origin = iPoint(this->position.x, this->position.y);
			iPoint origin2 = iPoint(app->scene->player->position.x, app->scene->player->position.y);


			if (position.DistanceTo(app->scene->player->position) < 320) {
						

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
				movX = (pos.x - this->position.x) / 30;
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
	}
		//Ataque

	if (AtackAnimDer.HasFinished() || currentAnimation != &AtackAnimDer) {
		AtackAnimDer.Reset();
		Ataca = false;
	}
	if (AtackAnimIzq.HasFinished() || currentAnimation != &AtackAnimIzq) {
		AtackAnimIzq.Reset();
		Ataca = false;
	}

	if (position.DistanceTo(app->scene->player->position) < 50 && currentAnimation != &AtackAnimDer) {
		
		currentAnimation = &AtackAnimDer;
		if (timertoplay > 250) {

			app->audio->PlayFx(torrentesound2, 0);
			timertoplay = 0;

		}
		timertoplay++;
		
		if (cooldown > 60) {
			int x = position.x + 60;
			int y = position.y + 15;
			b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
			ataque->body->SetTransform(newPos, ataque->body->GetAngle());
			cooldown = 0;

		}

	}
	if (position.DistanceTo(app->scene->player->position) < 150 && app->scene->player->position.x < position.x) {
		currentAnimation = &AtackAnimIzq;
		if (timertoplay > 250) {

			app->audio->PlayFx(torrentesound2, 0);
			timertoplay = 0;

		}
		timertoplay++;

		if (cooldown > 60) {
			int x = position.x - 20;
			int y = position.y + 15;
			b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
			ataque->body->SetTransform(newPos, ataque->body->GetAngle());
			cooldown = 0;
		}


	}
	
	if (position.DistanceTo(app->scene->player->position) > 50)
	{
		b2Vec2 ResetPos(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
		ataque->body->SetTransform(ResetPos, ataque->body->GetAngle());
		timerataque = 0;

	}
	
	vel.x = movX;
	/*if (punch == true && app->scene->player->position.x < position.x) {
		vel.x = PUNCHVELOCITY;		
		punch = false;
	}
	if (punch == true && app->scene->player->position.x >= position.x) {
		vel.x = -PUNCHVELOCITY;		
		punch = false;
	}*/
	//--------------TP-------------
	if (salto >= 200 && phase2 == true) {
		currentAnimation = &DesaparecerAnim;
		if (currentAnimation->HasFinished())
		{
		SetPosition(2700, 1674);
		salto = 0;
		}
		
	}
	if (salto >= 200 && phase2 == false) {
		currentAnimation = &DesaparecerAnim;
		if (currentAnimation->HasFinished())
		{
			SetPosition(2700, 1674);
			salto = 0;
		}
	}
	if (salto >= 0 && salto <= 10) {
		DesaparecerAnim.Reset();
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
	salto++;

	app->render->DrawTexture(texture, position.x -16 , position.y - 32, &currentAnimation->GetCurrentFrame());
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
