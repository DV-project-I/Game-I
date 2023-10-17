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
#include "Animation.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	
	IdleAnimIzq.PushBack({});
	IdleAnimIzq.PushBack({});
	IdleAnimIzq.PushBack({});
	IdleAnimIzq.PushBack({});
	IdleAnimIzq.speed = 0.15f;

	IdleAnimDer.PushBack({});
	IdleAnimDer.PushBack({});
	IdleAnimDer.PushBack({});
	IdleAnimDer.PushBack({});
	IdleAnimDer.speed = 0.15f;

	WalkAnimIzq.PushBack({});
	WalkAnimIzq.PushBack({});
	WalkAnimIzq.PushBack({});
	WalkAnimIzq.PushBack({});
	WalkAnimIzq.speed = 0.15f;


	WalkAnimDer.PushBack({});
	WalkAnimDer.PushBack({});
	WalkAnimDer.PushBack({});
	WalkAnimDer.PushBack({});
	WalkAnimDer.speed = 0.15f;

	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.PushBack({});
	JumpAnim.speed = 0.15f;
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

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	// Verifica si rect1 se superpone con rect2
	if (rect1.x + rect1.w > rect2.x && rect2.x + rect2.w > rect1.x &&
		rect1.y + rect1.h > rect2.y && rect2.y + rect2.h > rect1.y) {
		return true; // Hay colisi�n
	}
	return false; // No hay colisi�n
}

bool Player::Update(float dt)
{
	movX = 0;
	b2Vec2 vel = pbody->body->GetLinearVelocity(); // Obtener la velocidad actual
	
	if (vel.y == 0)
	{
		// Asegura que el jugador solo pueda saltar en el suelo
		isOnGround = true;
		
	}
	else
	{
		isOnGround = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && isOnGround) {
		
		vel.y = -JUMP_FORCE;
		
		//currentAnimation = &JumpAnim;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		// L�gica para agacharse
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		movX = -speed * dt;
		//currentAnimation = &WalkAnimIzq;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		movX = speed * dt;
		//currentAnimation = &WalkAnimDer;
	}

	vel.x = movX;  // Establece la velocidad horizontal
	

	pbody->body->SetLinearVelocity(vel);  // Aplica la velocidad al cuerpo del jugador

	vel.y -= GRAVITY_Y;	// Aplicar la gravedad

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	//currentAnimation->Update();
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