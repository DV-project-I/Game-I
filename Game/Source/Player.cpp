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
	
	IdleAnimIzq.PushBack({ 80, 112, 16, 16 });
	IdleAnimIzq.PushBack({ 96, 112, 16, 16 });
	IdleAnimIzq.PushBack({ 112, 112, 16, 16 });
	IdleAnimIzq.PushBack({ 128, 112, 16, 16 });
	IdleAnimIzq.speed = 0.05f;

	IdleAnimIzq.PushBack({ 80, 112, 16, 16 });
	IdleAnimIzq.PushBack({ 96, 112, 16, 16 });
	IdleAnimIzq.PushBack({ 112, 112, 16, 16 });
	IdleAnimIzq.PushBack({ 128, 112, 16, 16 });
	IdleAnimIzq.speed = 0.05f;

	WalkAnimIzq.PushBack({ 0, 128, 16, 16 });
	WalkAnimIzq.PushBack({ 16, 128, 16, 16 });
	WalkAnimIzq.PushBack({ 32, 128, 16, 16 });
	WalkAnimIzq.PushBack({ 48, 128, 16, 16 });
	WalkAnimIzq.speed = 0.15f;


	WalkAnimDer.PushBack({ 0, 112, 16, 16 });
	WalkAnimDer.PushBack({ 16, 112, 16, 16 });
	WalkAnimDer.PushBack({ 32, 112, 16, 16 });
	WalkAnimDer.PushBack({ 48, 112, 16, 16 });
	WalkAnimDer.speed = 0.15f;

	
	JumpAnim.PushBack({ 0, 80, 16, 16 });
	JumpAnim.PushBack({ 16, 80, 16, 16 });
	JumpAnim.PushBack({ 32, 80, 16, 16 });
	JumpAnim.PushBack({ 48, 80, 16, 16 });
	JumpAnim.PushBack({ 64, 80, 16, 16 });
	JumpAnim.PushBack({ 80, 80, 16, 16 });
	JumpAnim.PushBack({ 96, 80, 16, 16 });
	JumpAnim.PushBack({ 112, 80, 16, 16 });
	JumpAnim.PushBack({ 128, 80, 16, 16 });
	JumpAnim.PushBack({ 144, 80, 16, 16 });
	JumpAnim.speed = 0.3f;
	JumpAnim.loop = true;

	//JumpAnimIzq.PushBack({ 0, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 16, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 32, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 48, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 64, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 80, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 96, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 112, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 128, 64, 16, 16 });
	//JumpAnimIzq.PushBack({ 144, 64, 16, 16 });
	//JumpAnimIzq.speed = 0.3f;
	//JumpAnimIzq.loop = true;

	DeathAnim.PushBack({ 0, 160, 16, 16 });
	DeathAnim.PushBack({ 16, 160, 16, 16 });
	DeathAnim.PushBack({ 32, 160, 16, 16 });
	DeathAnim.PushBack({ 48, 160, 16, 16 });
	DeathAnim.PushBack({ 64, 160, 16, 16 });
	DeathAnim.speed = 0.1f;
	DeathAnim.loop = true;
}

Player::~Player() {

}

bool Player::Awake() {


	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	currentAnimation = &IdleAnimDer;

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x , position.y, 8, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");


	return true;
}

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	// Verifica si rect1 se superpone con rect2
	if (rect1.x + rect1.w > rect2.x && rect2.x + rect2.w > rect1.x &&
		rect1.y + rect1.h > rect2.y && rect2.y + rect2.h > rect1.y) {
		return true; // Hay colisión
	}
	return false; // No hay colisión
}

bool Player::Update(float dt)
{
	movX = 0;
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN ) {
		God = !God;
	}
	

	b2Vec2 vel = pbody->body->GetLinearVelocity(); // Obtener la velocidad actual

	//Estas quieto salta la IDLE
	if (vel.y == 0 && vel.x == 0 && IsDeath == false ) {
		currentAnimation = &IdleAnimIzq;
	}

	if (God == true) {
		speed = 0.5f;
		movY = 0;
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			movX = -speed * dt;
			
		}		
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			movX = speed * dt;			
		}
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			movY = -speed * dt;
			
		}		
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			movY = speed * dt;
			
		}
		IsDeath = false;
		vel.x = movX;
		vel.y = movY;
		pbody->body->SetLinearVelocity(vel);
	}
	else {
		// Asegura que el jugador solo pueda saltar en el suelo

		//Esta en el aire, Animacion salto


		//Espacio = saltar
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && isOnGround) {
			vel.y = -JUMP_FORCE;
			
			currentAnimation = &JumpAnim;


		}
		//Andar izquierda
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			movX = -speed * dt;
			if (isOnGround == true)
				currentAnimation = &WalkAnimIzq;
			if (isOnGround == false) {

				currentAnimation = &JumpAnim;
			}
		}

		//Andar derecha
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			movX = speed * dt;
			if (isOnGround == true)
				currentAnimation = &WalkAnimDer;
			if (isOnGround == false) {

				currentAnimation = &JumpAnim;
			}
		}
		// Establece la velocidad horizontal
	vel.x = movX; 
	
	// Aplica la velocidad al cuerpo del jugador
	pbody->body->SetLinearVelocity(vel);  

	// Aplicar la gravedad
	vel.y -= GRAVITY_Y;	
	}
	

	

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	currentAnimation->Update();
	
	app->render->DrawTexture(texture, position.x +8, position.y +8, &currentAnimation->GetCurrentFrame());
	
	if (IsDeath == true) {
		PlayerDeath();
		//pbody->body->SetTransform(b2Vec2(200, 300), 360);
	}
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
		//app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::PLATFORM:
		isOnGround = true;
		LOG("Collision PLATFORM");
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	case ColliderType::INSTAKILL:
		IsDeath = true;
		LOG("Collision INSTAKILL");
		break;
	}
	

}

void Player :: PlayerDeath()
{
	
	position.x = 200;
	position.y = 300;
	currentAnimation = &DeathAnim;
	IsDeath = false;
	
}

	


