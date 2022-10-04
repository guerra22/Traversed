#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "SDL/include/SDL.h"

#include "PugiXml\src\pugixml.hpp"

// L03: DONE 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;

	SDL_Texture* texture;
	int	texWidth;
	int	texHeight;
	int	tilecount;
	int	columns;

	// L04: DONE 7: Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;
};

// L03: DONE 1: We create an enum for map type, just for convenience,
// NOTE: Platformer game will be of type ORTHOGONAL
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// L06: TODO 5: Create a generic structure to hold properties
struct Properties
{
	struct Property
	{
		//...
		SString name;
		int value;
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
		list.clear();
	}

	// L06: TODO 7: Method to ask for the value of a custom property
	int GetProperty(const char* name, int default_value = 0) const;

	List<Property*> list;
};

// L04: DONE 1: Create a struct for the map layer
struct MapLayer
{
	SString	name;
	int width;
	int height;
	uint* data;

	// L06: DONE 1: Support custom properties
	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	// L04: DONE 6: Short function to get the value of x,y
	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

struct Object {
	SString name;
	int type;
	int id;
	int x;
	int y;
};

struct ObjectGroup {
	SString name;
	List<Object*> objects;
};

enum class ColliderLayerType {
	SPAWN = 287,
	END,
	NORMAL,
	SPIKE,
	PLATFORM
};

// L03: DONE 1: Create a struct needed to hold the information to Map node
struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;

	int map_width;
	int map_height;

	SDL_Color backgroundColor;
	MapTypes type;
	List<TileSet*> tilesets;

	// L04: DONE 2: Add a list/array of layers to the map
	List<MapLayer*> layers;
	List<ObjectGroup*> objectGroups;

	inline void Clear() {
		// Clear tilesets
		ListItem<TileSet*>* item;
		item = tilesets.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}
		tilesets.clear();

		// Clear layers
		ListItem<MapLayer*>* item2;
		item2 = layers.start;

		while (item2 != NULL)
		{
			RELEASE(item2->data);
			item2 = item2->next;
		}
		layers.clear();

		// Clear objectgroups
		ListItem<ObjectGroup*>* objg;
		objg = objectGroups.start;

		while (objg != NULL) {
			ListItem<Object*>* obj;
			obj = objg->data->objects.start;

			while (obj != NULL) {
				RELEASE(obj->data);
				obj = obj->next;
			}
			objg->data->objects.clear();

			RELEASE(objg->data);
			objg = objg->next;
		}
		objectGroups.clear();
	}
};

class Map : public Module
{
public:

	Map();

	// Destructor
	virtual ~Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;
	iPoint MapToWorld(iPoint pos) const;

	// L05: DONE 2: Add orthographic world to map coordinates
	iPoint WorldToMap(int x, int y) const;
	iPoint WorldToMap(iPoint position) const;

	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;
private:

	// L03: Methods to load all required map data
	bool LoadMap(pugi::xml_node mapFile);
	bool LoadTileSets(pugi::xml_node mapFile);
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);

	// L04
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadAllLayers(pugi::xml_node mapNode);

	bool LoadObjectGroup(pugi::xml_node& node, ObjectGroup* objectGroup);
	bool LoadAllObjectGroups(pugi::xml_node& mapNode);

	// L06: TODO 6: Load a group of properties 
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	// L06: TODO 3: Pick the right Tileset based on a tile id
	TileSet* GetTilesetFromTileId(int id) const;
public:

	// L03: DONE 1: Add your struct for map info
	MapData mapData;

private:

	SString folder;
	bool mapLoaded;
};

#endif // __MAP_H__