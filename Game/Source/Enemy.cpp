#include "Enemy.h"
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

//Enemy::Enemy() : Entity(EntityType::ENEMY)
//{
//	name.Create("Enemy");
//
//}
//
//Player::~Player() {
//
//}
//
//bool Enemy::Awake() {
//
//
//	position.x = parameters.attribute("x").as_int();
//	position.y = parameters.attribute("y").as_int();
//	texturePath = parameters.attribute("texturepath").as_string();
//	currentAnimation = &IdleAnimDer;
//
//	return true;
//}
//
//bool Enemy::Start() {
//
//	//initilize textures
//	texture = app->tex->Load(texturePath);
//
//
//	hp = 10;
//	//texture = app->tex->Load("Assets/personajes/Spritesheet Parca/parca.png");
//
//	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);
//	pbody->listener = this;
//	pbody->ctype = ColliderType::PLAYER;
//
//	//pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");
//
//
//	return true;
//}