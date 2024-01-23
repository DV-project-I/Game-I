#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "../bat.h"
#include "Tree.h"

#include "GuiControl.h"
#include "GuiControlButton.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool SaveState(pugi::xml_node node);

	bool LoadState(pugi::xml_node node);

	bool OnGuiMouseClickEvent(GuiControl* control);

	iPoint GetPLayerPosition();

	Player* player;

	GuiControlButton* pause;
private:

	SDL_Texture* img;
	SDL_Texture* conf;
	float textPosX, textPosY = 0;
	uint texW, texH;
	uint windowW, windowH;	
	SDL_Texture* mouseTileTex = nullptr;
	
	Enemy* enemy;
	Tree* tree;
	Bat* bat;
	PhysBody* pbody;

	
	GuiControlButton* exit;
	GuiControlButton* volume;
	GuiControlButton* back;
	GuiControlButton* fullscreen;
	GuiControlButton* vsync;
};

#endif // __SCENE_H__