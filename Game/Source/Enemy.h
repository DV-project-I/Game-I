#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"


struct SDL_Texture;

class Enemy : public Entity
{
public:
	
	Enemy();
	
	virtual ~Enemy();

	bool Awake();
	
	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);


public:
	float speed;
	const char* texturePath;
	int hp;
	SDL_Texture* texture = NULL;
	Animation* currentAnimation = nullptr;
	PhysBody* pbody;
	//int pickCoinFxId;

	PhysBody* ataque;


	float movX;
	float movY;
	float velY;
	float acc;
	const float JUMP_INITIAL_VELOCITY = 200.0f;
	bool isJumping;
	bool isOnGround;
	float JUMP_FORCE = 10.0f;

	Animation IdleAnimIzq;
	Animation IdleAnimDer;
	Animation WalkAnimIzq;
	Animation WalkAnimDer;
	Animation JumpAnim;
	Animation AtackAnim;
	Animation DeathAnim;
	Animation JumpAnimIzq;

	Animation Batfly;
	Animation BatAtack;
	Animation TreeWalk;
	Animation TreeAtack;

};

#endif // __ENEMY_H__
