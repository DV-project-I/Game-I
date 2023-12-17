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
	
	IdleAnimDer.PushBack({ 0, 160, 32, 32 });
	IdleAnimDer.PushBack({ 32, 160, 32, 32 });
	IdleAnimDer.PushBack({ 64, 160, 32, 32 });
	IdleAnimDer.PushBack({ 96, 160, 32, 32 });
	IdleAnimDer.speed = 0.05f;

	IdleAnimIzq.PushBack({ 0, 192, 32, 32 });
	IdleAnimIzq.PushBack({ 32, 192, 32, 32 });
	IdleAnimIzq.PushBack({ 64, 192, 32, 32 });
	IdleAnimIzq.PushBack({ 96, 192, 32, 32 });
	IdleAnimIzq.speed = 0.05f;

	WalkAnimIzq.PushBack({ 0, 224, 32, 32 });
	WalkAnimIzq.PushBack({ 32, 224, 32, 32 });
	WalkAnimIzq.PushBack({ 64, 224, 32, 32 });
	WalkAnimIzq.PushBack({ 96, 224, 32, 32 });
	WalkAnimIzq.speed = 0.15f;


	WalkAnimDer.PushBack({ 0, 256, 32, 32 });
	WalkAnimDer.PushBack({ 32, 256, 32, 32 });
	WalkAnimDer.PushBack({ 64, 256, 32, 32 });
	WalkAnimDer.PushBack({ 96, 256, 32, 32 });
	WalkAnimDer.speed = 0.15f;

	
	JumpAnimIzq.PushBack({ 0, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 32, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 64, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 96, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 128, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 160, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 192, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 224, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 256, 96, 32, 32 });
	JumpAnimIzq.PushBack({ 288, 96, 32, 32 });
	JumpAnimIzq.speed = 0.3f;
	JumpAnim.loop = true;

	JumpAnim.PushBack({ 0, 128, 32, 32 });
	JumpAnim.PushBack({ 32, 128, 32, 32 });
	JumpAnim.PushBack({ 64, 128, 32, 32 });
	JumpAnim.PushBack({ 96, 128, 32, 32 });
	JumpAnim.PushBack({ 128, 128, 32, 32 });
	JumpAnim.PushBack({ 160, 128, 32, 32 });
	JumpAnim.PushBack({ 192, 128, 32, 32 });
	JumpAnim.PushBack({ 224, 128, 32, 32 });
	JumpAnim.PushBack({ 256, 128, 32, 32 });
	JumpAnim.PushBack({ 288, 128, 32, 32 });
	JumpAnim.speed = 0.3f;
	JumpAnimIzq.loop = true;

	DeathAnim.PushBack({ 0, 288, 32, 32 });
	DeathAnim.PushBack({ 32, 288, 32, 32 });
	DeathAnim.PushBack({ 64, 288, 32, 32 });
	DeathAnim.PushBack({ 96, 288, 32, 32 });
	DeathAnim.PushBack({ 128, 288, 32, 32 });
	DeathAnim.speed = 0.1f;
	DeathAnim.loop = false;

	AtackAnimDer.PushBack({ 0, 33, 32, 32 });
	AtackAnimDer.PushBack({ 32, 33, 32, 32 });
	AtackAnimDer.PushBack({ 64, 33, 32, 32 });
	AtackAnimDer.PushBack({ 96, 33, 32, 32 });
	AtackAnimDer.PushBack({ 128, 33, 32, 32 });
	AtackAnimDer.speed = 0.1f;
	AtackAnimDer.loop = false;

	AtackAnimIzq.PushBack({ 0, 0, 32, 32 });
	AtackAnimIzq.PushBack({ 32, 0, 32, 32 });
	AtackAnimIzq.PushBack({ 64, 0, 32, 32 });
	AtackAnimIzq.PushBack({ 96, 0, 32, 32 });
	AtackAnimIzq.PushBack({ 128, 0, 32, 32 });
	AtackAnimIzq.speed = 0.1f;
	AtackAnimIzq.loop = false;

	
	
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
	walkingsound = app->audio->LoadFx("Assets/Audio/Fx/walking.wav");


	hp = 10;
	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");

	pbody = app->physics->CreateCircle(position.x , position.y, 8, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	ataque = app->physics->CreateRectangle(0, 0, 8, 16, bodyType::STATIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::ITEM;
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
	
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		IsDeath = true;
	}
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN ) {
		God = !God;
	}
	

	b2Vec2 vel = pbody->body->GetLinearVelocity(); // Obtener la velocidad actual

	//Estas quieto salta la IDLE
	if (vel.y == 0 && vel.x == 0 && IsDeath == false && currentAnimation == &WalkAnimIzq) {
		currentAnimation = &IdleAnimIzq;
		left = true;
	}
	if (vel.y == 0 && vel.x == 0 && IsDeath == false && currentAnimation == &WalkAnimDer) {
		currentAnimation = &IdleAnimDer;
		left = false;
	}
	

	if (God == true) {

		IsDeath = false;
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
		vel.x = movX;
		vel.y = movY;
		pbody->body->SetLinearVelocity(vel);
	}
	else if(IsDeath == false) {
		speed = 0.25f;

		if (vel.y == 0) {
			isOnGround = true;
			/*currentAnimation = &IdleAnimIzq;*/
		}
		else {
			isOnGround = false;
		}
		//Espacio = saltar
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && isOnGround == true ) {
			vel.y = -JUMP_FORCE;			
			currentAnimation = &JumpAnim;
		}
		//Andar izquierda
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			movX = -speed * dt;
			if (isOnGround == true)
				currentAnimation = &WalkAnimIzq;
			if (isOnGround == false) {
				currentAnimation = &JumpAnimIzq;
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
	
	//ATAQUE BASICO MELÉ
	if (app->input->GetMouseButtonDown(1) == KEY_DOWN && currentAnimation == &WalkAnimIzq || app->input->GetMouseButtonDown(1) == KEY_DOWN && currentAnimation == &IdleAnimIzq || app->input->GetMouseButtonDown(1) == KEY_DOWN && currentAnimation == &JumpAnimIzq ) {
		currentAnimation = &AtackAnimDer;
		pbody->height = 16;		
		pbody->ctype = ColliderType::PLAYERATTACK;
			
		if (AtackAnimDer.HasFinished() == true)
		{
			pbody->height = 8;
			pbody->ctype = ColliderType::PLAYER;
			AtackAnimDer.Reset();
			
		}
		
		
	}
	if (app->input->GetMouseButtonDown(1) == KEY_DOWN && currentAnimation == &WalkAnimDer || app->input->GetMouseButtonDown(1) == KEY_DOWN && currentAnimation == &IdleAnimDer || app->input->GetMouseButtonDown(1) == KEY_DOWN && currentAnimation == &JumpAnim) {
		currentAnimation = &AtackAnimIzq;
		pbody->height = 16;
		pbody->ctype = ColliderType::PLAYERATTACK;

		if (AtackAnimDer.HasFinished() == true)
		{
			pbody->height = 8;
			pbody->ctype = ColliderType::PLAYER;
			AtackAnimIzq.Reset();
			
		}
	
		
		
	}


	if (vel.y == 0 && vel.x == 0 && IsDeath == false && currentAnimation == &WalkAnimIzq) {
		currentAnimation = &IdleAnimIzq;
		left = true;
	}
	if (vel.y == 0 && vel.x == 0 && IsDeath == false && currentAnimation == &WalkAnimDer) {
		currentAnimation = &IdleAnimDer;
		left = false;
	}


	if (hp <= 0) {
		IsDeath == true;
	}


	if (IsDeath == true) {
		PlayerDeath();	
		
	}
	

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 24;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 24;

	currentAnimation->Update();
	
	app->render->DrawTexture(texture, position.x +8, position.y +9, &currentAnimation->GetCurrentFrame());

	if (isOnGround == true && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && timertoplay > 31 || isOnGround == true && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && timertoplay > 31) {

		timertoplay = 0;
		
		app->audio->PlayFx(walkingsound, 0);
		
	}

	timertoplay++;
	
	
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
		LOG("Collision PLATFORM");
		currentAnimation = &IdleAnimDer;

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

void Player ::SetPosition(int x, int y) {
	DeathAnim.Reset();
	position.x = x;
	position.y = y;
	b2Vec2 newPos(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	pbody->body->SetTransform(newPos, pbody->body->GetAngle());	
	
	IsDeath = false;
	
}

void Player :: PlayerDeath()
{			
	currentAnimation = &DeathAnim;
	if (currentAnimation->HasFinished() == true) {		
		SetPosition(parameters.attribute("x").as_int(), parameters.attribute("y").as_int());		
	}
	
}




