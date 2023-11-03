#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"


struct SDL_Texture;

class Player : public Entity
{
public:
	// Constructor
	Player();
	// Destructor
	virtual ~Player();

	bool Awake();
	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void PlayerDeath();

public:
	float speed = 0.2f;
	const char* texturePath;
	SDL_Texture* texture = NULL;
	Animation* currentAnimation = nullptr;
	PhysBody* pbody;
	int pickCoinFxId;

	bool IsDeath = false;
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
};

#endif // __PLAYER_H__