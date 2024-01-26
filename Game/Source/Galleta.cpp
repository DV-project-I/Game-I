#include "Galleta.h"
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

Galleta::Galleta() : Entity(EntityType::GALLETA)
{
	name.Create("galleta");	
	alma.PushBack({ 0, 0, 16, 16 });
	alma.PushBack({ 16, 0, 16, 16 });
	alma.PushBack({ 32, 0, 16, 16 });
	alma.PushBack({ 48, 0, 16, 16 });
	alma.PushBack({ 64, 0, 16, 16 });
	alma.PushBack({ 80, 0, 16, 16 });
	alma.speed = 0.2f;
	alma.loop = true;
}

Galleta::~Galleta() {}

bool Galleta::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentanim = &alma;
	
	return true;
}

bool Galleta::Start() {
	
	
	//initilize textures
	texture = app->tex->Load("Assets/cosas/galleta.png");
	pbody = app->physics->CreateCircle(position.x + 8, position.y + 8, 8, bodyType::DYNAMIC, true);
	pbody->ctype = ColliderType::GALLETA;
	pbody->listener = this;
	pbody->body->SetGravityScale(0);
	return true;
}



bool Galleta::Update(float dt)
{
	currentanim->Update();
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	
	app->render->DrawTexture(texture, position.x +8, position.y +8);
	
	return true;
}

bool Galleta::CleanUp()
{
	return true;
}

void Galleta::OnCollision(PhysBody* physA, PhysBody* physB) {
	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");
		usado = true;
		app->physics->DestroyObject(pbody);
		//app->audio->PlayFx(pickCoinFxId);
		app->entityManager->DestroyEntity(this);
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

