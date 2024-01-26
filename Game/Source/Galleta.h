#ifndef __GALLETA_H__
#define __GALLETA_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Galleta : public Entity
{
public:

	Galleta();
	virtual ~Galleta();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void SetPosition(int x, int y);

public:

	bool isPicked = false;
	Animation* currentanim = nullptr;
private:

	SDL_Texture* texture;
	Animation alma;
	bool usado = false;

	
	const char* texturePath;
	PhysBody* pbody;
};

#endif // __ITEM_H__