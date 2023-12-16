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

Bat::Bat() : Entity(EntityType::BAT)
{
	name.Create("bat");
	Batfly.PushBack({ 0, 0, 32, 32 });
	Batfly.PushBack({ 32, 0, 32, 32 });
	Batfly.PushBack({ 64, 0, 32, 32 });
	Batfly.PushBack({ 96, 0, 32, 32 });
	Batfly.PushBack({ 128, 0, 32, 32 });

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




	hp = 10;
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ENEMY;

	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");


	return true;
}


bool Bat::Update(float dt) {



	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->render->DrawTexture(texture, position.x + 3, position.y);
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
	}


}
