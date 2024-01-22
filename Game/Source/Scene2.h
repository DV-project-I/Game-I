#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "../bat.h"
#include "Tree.h"

#include "GuiControl.h"
#include "GuiControlButton.h"

struct SDL_Texture;

class Scene2 : public Module
{
public:

	Scene2();

	// Destructor
	virtual ~Scene2();

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



	bool OnGuiMouseClickEvent(GuiControl* control);

	
private:

	SDL_Texture* img;
	SDL_Texture* conf;
	float textPosX, textPosY = 0;
	uint texW, texH;
	uint windowW, windowH;	
	SDL_Texture* mouseTileTex = nullptr;


	GuiControlButton* gcButtom;
};

#endif // __SCENE_H__