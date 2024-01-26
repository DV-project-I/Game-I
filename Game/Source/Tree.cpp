#include "Tree.h"
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

Tree::Tree() : Entity(EntityType::TREE)
{
	name.Create("tree");


	IdleAnim.PushBack({ 0, 64, 64, 64 });
	IdleAnim.PushBack({ 64, 64, 64, 64 });
	IdleAnim.PushBack({ 128, 64, 64, 64 });
	IdleAnim.speed = 0.1f;
	IdleAnim.loop = true;


	AtackAnim.PushBack({ 0, 0, 64, 64 });
	AtackAnim.PushBack({ 64, 0, 64, 64 });
	AtackAnim.PushBack({ 128, 0, 64, 64 });
	AtackAnim.PushBack({ 192, 0, 64, 64 });
	AtackAnim.PushBack({ 256, 0, 64, 64 });	
	AtackAnim.PushBack({ 320, 0, 64, 64 });
	AtackAnim.PushBack({ 384, 0, 64, 64 });
	AtackAnim.PushBack({ 448, 0, 64, 64 });
	AtackAnim.PushBack({ 512, 0, 64, 64 });
	AtackAnim.PushBack({ 576, 0, 64, 64 });
	AtackAnim.PushBack({ 640, 0, 64, 64 });
	AtackAnim.PushBack({ 704, 0, 64, 64 });
	AtackAnim.speed = 0.3f;
	AtackAnim.loop = true;



	DeathAnim.PushBack({ 192, 64, 64, 64});
	DeathAnim.PushBack({ 256,64, 64, 64 });
	DeathAnim.PushBack({ 320,64, 64, 64 });
	DeathAnim.PushBack({ 384,64, 64, 64 });
	DeathAnim.speed = 0.1f;
	DeathAnim.loop = false;
}

Tree::~Tree() {

}

bool Tree::Awake() {


	
PathFinding path;
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentAnimation = &IdleAnim;

	return true;
}

bool Tree::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);
	camino = app->tex->Load("Assets/Textures/camino.png");
	torrentesound = app->audio->LoadFx("Assets/Audio/Fx/torrente.wav");
	torrentesound2 = app->audio->LoadFx("Assets/Audio/Fx/punchtorrente.wav");
	
	
	cooldown = 0;
	hp = 10;
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateRectangle(position.x, position.y, 16, 32, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	ataque = app->physics->CreateRectangle(0, 0, 20, 20, bodyType::STATIC);
	ataque->ctype = ColliderType::ENEMY;
	ataque->body->GetFixtureList()->SetSensor(true);

	
	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");


	return true;
}


bool Tree::Update(float dt) {
	
	
	

	if (app->scene->player->IsDeath == true) {
		IsDeath = false;
		pbody->height = 64;
		pbody->ctype = ColliderType::ENEMY;
	}

	if (IsDeath == true) {
		
		currentAnimation = &DeathAnim;
		pbody->height = 32;		
		pbody->ctype = ColliderType::ITEM;
	
	}
	else {
		
			
		

		if (position.DistanceTo(app->scene->player->position) < 50 ) {
			currentAnimation = &AtackAnim;
			//app->audio->PlayFx(torrentesound2, 0);
			if (cooldown > 60) {
				int x = app->scene->player->position.x + 7;
				int y = app->scene->player->position.y + 20;
				b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
				ataque->body->SetTransform(newPos, ataque->body->GetAngle());
				timerataque = 0;
				cooldown = 0;
			}
		}
	}
	if (timerataque >= 30)
	{
		b2Vec2 ResetPos(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
		ataque->body->SetTransform(ResetPos, ataque->body->GetAngle());
		timerataque = 0;
		
	}
	

	currentAnimation->Update();

	

	this->position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	this->position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	

	app->render->DrawTexture(texture, position.x -16 , position.y -25, &currentAnimation->GetCurrentFrame());
	
	timerataque++;
	cooldown++;

	currentAnimation = &IdleAnim;
	return true;
}

bool Tree::CleanUp() {
	return true;
}

void Tree::OnCollision(PhysBody* physA, PhysBody* physB) {
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
		app->scene->player->contadorcookies++;
		LOG("Collision PLAYERATTACK");
		break;
	}


}
void Tree::SetPosition(int x, int y) {
	DeathAnim.Reset();
	position.x = x;
	position.y = y;
	b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	pbody->body->SetTransform(newPos, pbody->body->GetAngle());

	IsDeath = false;

}

