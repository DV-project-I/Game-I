#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "DynArray.h"
#include "Pathfinding.h"

#include "PugiXml\src\pugixml.hpp"

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;
	int columns;
	int tilecount;

	SDL_Texture* texture;

	SDL_Rect GetRect(uint gid) {
		SDL_Rect rect = { 0 };

		int relativeIndex = gid - firstgid;
		rect.w = tileWidth;
		rect.h = tileHeight;
		rect.x = margin + (tileWidth + spacing) * (relativeIndex % columns);
		rect.y = margin + (tileHeight + spacing) * (relativeIndex / columns);

		return rect;
	}
};


struct Properties
{
	struct Property
	{
		SString name;
		bool value;
	};

	~Properties()
	{
		//...
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.Clear();
	}

	Property* GetProperty(const char* name);

	List<Property*> list;
};

struct MapLayer
{
	SString	name;
	int id; 
	int width;
	int height;
	uint* data;
	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	List<TileSet*> tilesets;
	MapTypes type;

	List<MapLayer*> maplayers;
	List<PhysBody*> m_collisiones;
};

class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

    // Called before quitting
    bool CleanUp();

    // Load new map
	bool Load(SString mapFileName);

	bool LoadObjectGroups(pugi::xml_node mapNode);

	iPoint MapToWorld(int x, int y) const;

	iPoint Map::WorldToMap(int x, int y);

	bool LoadMap(pugi::xml_node mapFile);

	bool LoadTileSet(pugi::xml_node mapFile);

	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

	bool LoadAllLayers(pugi::xml_node mapNode);

	TileSet* GetTilesetFromTileId(int gid) const;

	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	void CreateNavigationMap(int& width, int& height, uchar** buffer) const;

	

	int GetTileWidth();
	int GetTileHeight();

public: 

	MapData mapData;
	SString name;
	SString path;
	PathFinding* pathfinding;
private:

	bool mapLoaded;
	MapLayer* navigationLayer;
	int blockedGid = 1; //!!!! make sure that you assign blockedGid according to your map

};

#endif // __MAP_H__