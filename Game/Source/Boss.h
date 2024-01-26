#ifndef __BOSS_H__
#define __BOSS_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "Bullet.h"
#include "Player.h"


struct SDL_Texture;

class Boss : public Entity
{
public:
	
	Boss();
	
	virtual ~Boss();

	bool Awake();
	
	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	

	void EnemyDeath();

	void SetPosition(int x, int y);



public:
	float speed;
	const char* texturePath;
	int hp;
	SDL_Texture* texture = NULL;
	SDL_Texture* camino = NULL;
	Animation* currentAnimation = nullptr;
	PhysBody* pbody;
	//int pickCoinFxId;

	
	Bullet* bullet;
	float timertoplay;
	
	uint torrentesound;
	uint torrentesound2;

	
	PhysBody* ataque;
	float timerataque = 0;
	float cooldown = 0;
	float salto = 0;

	float movX;
	float movY;
	float velY;	
	bool IsDeath = false;
	bool pathmode = false;
	bool punch = false;

	const float PUNCHVELOCITY = 400.0f;

	bool derecha = false;
	bool phase2 = false;
	bool Ataca;
	bool ganaste = false;

	Animation IdleAnimIzq;
	Animation IdleAnimDer;
	Animation WalkAnimIzq;
	Animation WalkAnimDer;
	Animation JumpAnim;
	Animation AtackAnimDer;
	Animation AtackAnimIzq;
	Animation DeathAnim;
	Animation JumpAnimIzq;
	Animation DesaparecerAnim;



};

#endif // __BOSS_H__
