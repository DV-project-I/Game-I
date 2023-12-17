#ifndef __BAT_H__
#define __BAT_H__

#include "../Entity.h"
#include "../Point.h"
#include "SDL/include/SDL.h"
#include "../Animation.h"


struct SDL_Texture;

class Bat : public Entity
{
public:

	Bat();

	virtual ~Bat();

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
	SDL_Texture* camino = NULL;
	Animation* currentAnimation = nullptr;
	PhysBody* pbody;
	//int pickCoinFxId;

	SDL_Rect AreaVision;

	PhysBody* ataque;


	float movX;
	float movY;
	float velY;
	float acc;
	const float JUMP_INITIAL_VELOCITY = 200.0f;
	bool isJumping;
	bool isOnGround;
	float JUMP_FORCE = 10.0f;

	bool Ataca;

	Animation Batfly;
	Animation BatAtack;


};

#endif // __ENEMY_H__

