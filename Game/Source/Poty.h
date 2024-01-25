#ifndef __POTY_H__
#define __POTY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Poty : public Entity
{
public:

	Poty();
	virtual ~Poty();

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