#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	return true;
}

bool Player::Update(float dt)
{
	movX = 0;
	b2Vec2 vel = pbody->body->GetLinearVelocity(); // Obtener la velocidad actual

	// Aplicar la gravedad
	vel.y -= GRAVITY_Y;

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		// Aplicar una fuerza hacia arriba para el salto
		if (vel.y == 0.0f) {  // Asegura que el jugador solo pueda saltar en el suelo
			vel.y = JUMP_FORCE;  // Establece la velocidad vertical para el salto
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		// Lógica para agacharse
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		movX = -speed * dt;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		movX = speed * dt;
	}

	vel.x = movX;  // Establece la velocidad horizontal

	pbody->body->SetLinearVelocity(vel);  // Aplica la velocidad al cuerpo del jugador

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}


bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}