#ifndef __BULLET_H__
#define __BULLET__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Bullet : public Entity
{
public:

	Bullet();
	virtual ~Bullet();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:

	bool isPicked = false;
	Animation* currentanim = nullptr;
private:

	SDL_Texture* texture;
	Animation alma;
	
	const char* texturePath;
	PhysBody* pbody;
};

#endif // __ITEM_H__