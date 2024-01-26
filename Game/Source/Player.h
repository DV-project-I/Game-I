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

	void SetPosition(int x, int y);

public:
	float speed;
	const char* texturePath;
	int hp = 10;
	SDL_Texture* texture = NULL;
	SDL_Texture* tataque = NULL;
	Animation* currentAnimation = nullptr;
	PhysBody* pbody;
	PhysBody* ataque;
	PhysBody* tpnivel2;
	PhysBody* tpBoss;

	int pickCoinFxId;

	int patata = 0;
	bool lvl2 = false;
	bool bossfight = false;
	bool pasaste = false;
	bool pasaste2 = false;
	bool left;
	bool God;
	bool IsDeath = false;
	float movX;
	float movY;
	float velY;
	float acc;
	float timertoplay;

	int contadorcookies = 0;

	const float JUMP_INITIAL_VELOCITY = 200.0f;
	bool isJumping;
	bool isOnGround;
	bool isPlayingSound;
	bool isPlayingAtack = false;
	float JUMP_FORCE = 10.0f;

	int vidas = 5;

	uint walkingsound;
	uint grito;
	uint ataquesonido;
	uint galleta;

	float timerataque;

	Animation IdleAnimIzq;
	Animation IdleAnimDer;
	Animation WalkAnimIzq;
	Animation WalkAnimDer;
	Animation JumpAnim;
	Animation AtackAnimDer;
	Animation AtackAnimIzq;
	Animation DeathAnim;
	Animation JumpAnimIzq;
	Animation Alma;


};

#endif // __PLAYER_H__