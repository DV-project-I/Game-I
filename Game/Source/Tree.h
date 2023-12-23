#ifndef __TREE_H__
#define __TREE_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"


struct SDL_Texture;

class Tree : public Entity
{
public:
	
	Tree();
	
	virtual ~Tree();

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

	float timertoplay;

	uint torrentesound;
	uint torrentesound2;

	PhysBody* ataque;


	float movX;
	float movY;
	float velY;	
	bool IsDeath = false;
	bool pathmode = false;

	bool Ataca;


	Animation IdleAnim;
	Animation AtackAnim;
	Animation DeathAnim;

};

#endif // __TREE_H__
