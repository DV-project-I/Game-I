#include "Bullet.h"
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
#include "Boss.h"

Bullet::Bullet() : Entity(EntityType::BULLET)
{
	name.Create("bullet");
}

Bullet::~Bullet() {}

bool Bullet::Awake() {

	position.x = app->scene->boss->position.y;
	position.y = app->scene->boss->position.y;
	
	
	return true;
}

bool Bullet::Start() {
	
	//initilize textures
	texture = app->tex->Load("Assets/personajes/Boss/BloodBall.png");
	pbody = app->physics->CreateCircle(position.x + 8, position.y + 8, 8, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ENEMY;
	
	return true;
}



bool Bullet::Update(float dt)
{
	movY = 0;
	
	b2Vec2 vel;
	if (app->scene->player->position.x < app->scene->boss->position.x) {

		movX = -30;
	}
	if (app->scene->player->position.x > app->scene->boss->position.x) {

		movX = 30;
	}
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	

	vel.x = movX;
	vel.y = movY;
	
	pbody->body->SetLinearVelocity(vel);
	if (timer >= 2000) {
		app->entityManager->DestroyEntity(this);
	}
	app->render->DrawTexture(texture, position.x +8, position.y +8);
	timer++;
	return true;
}

bool Bullet::CleanUp()
{
	return true;
}

void Bullet::OnCollision(PhysBody* physA, PhysBody* physB) {
	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
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
		LOG("Collision PLAYERATTACK");
		break;
	}


}