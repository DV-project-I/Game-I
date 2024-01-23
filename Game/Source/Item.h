#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Item : public Entity
{
public:

	Item();
	virtual ~Item();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

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