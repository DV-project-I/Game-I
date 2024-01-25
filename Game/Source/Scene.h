#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "../bat.h"
#include "Tree.h"
#include "Boss.h"

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
	float volumen = 90;
	GuiControlButton* pause;
	SDL_Texture* diescreen;
	SDL_Texture* winscreen;
private:
	bool onpause;
	SDL_Texture* img;
	SDL_Texture* conf;
	SDL_Texture* boton1;
	SDL_Texture* boton2;
	SDL_Texture* fondo;
	SDL_Texture* patras;
	SDL_Texture* vol;
	SDL_Texture* novol;
	SDL_Texture* fuera;
	


	float textPosX, textPosY = 0;
	uint texW, texH;
	uint windowW, windowH;	
	SDL_Texture* mouseTileTex = nullptr;
	
	Enemy* enemy;
	Tree* tree;
	Bat* bat;
	PhysBody* pbody;
	Item* item;
	Boss* boss;
	
	GuiControlButton* exit;
	GuiControlButton* volume;
	GuiControlButton* back;
	GuiControlButton* fullscreen;
	GuiControlButton* vsync;

	
};

#endif // __SCENE_H__