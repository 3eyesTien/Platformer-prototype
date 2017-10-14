#include "level.h"
#include "graphics.h"
#include "globals.h"
#include "tinyxml2.h"

#include <SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) : 
		mapName(mapName),
		spawnPoint(spawnPoint),
		size(Vector2(0, 0)) {
	this->loadMap(mapName, graphics);
}
Level::~Level() {

}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
	//Parse the .tmx file
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/maps/" << mapName << ".tmx";		//Pass in map1, we get map1.tmx
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	//Get the width and height of the whole map and store it in size
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->size = Vector2(width, height);

	//Get the width and height of the tiles and store it into tileSize
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->tileSize = Vector2(tileWidth, tileHeight);

	//Loading the tilesets
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL)
	{
		while (pTileset)
		{
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			std::string path = source;	//Makes the path into a string of the source rather than char*
			path.erase(0, 2);			//Deletes the ".." at the beginning of the source element value
			std::stringstream ss;			//just the string stream
			ss << "content" << path;		//Now ss should read "content/tilesets/blah.png"

			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
			this->tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	//Loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL)
	{
		while (pLayer)
		{
			//Loading the data element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL)
			{
				while (pData)
				{
					//Loading the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL)
					{
						int tileCounter = 0;
						while (pTile) 
						{
							//Build each individual tile here
							//If gid is 0, no tile should be drawn. Continue loop
							if (pTile->IntAttribute("gid") == 0)
							{
								tileCounter++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else 
								{
									break;
								}
							}
							//Get the tileset for the specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (unsigned int i = 0; i < this->tilesets.size(); i++)
							{
								if (this->tilesets[i].FirstGid <= gid)
								{
									//This is the tileset we want
									tls = this->tilesets.at(i);
									break;
								}
							}

							if (tls.FirstGid == -1)
							{
								//No tileset was found for this gid
								tileCounter++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}

							//Get the position of the tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							//Calculate the position of the tile on the tileset
							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileWidth) - 1;  //Grab which column the tile is located in
							tsxx *= tileWidth;
							
							int tsyy = 0;
							int amt = (gid / (tilesetWidth / tileWidth));
								
							tsyy = tileHeight * amt;  //Grab which row the tile is in
						
							//cout << "tsxx: " << tsxx << endl;
							//cout << "amt: " << amt << endl;
							//cout << "tsyy: " << tsyy << endl;
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);	//Get the tile position on the tileset

							//Build the actual tile and add it to the level's tile list
							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							this->tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}


					pData = pData->NextSiblingElement("data");
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}
}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
	for (unsigned int i = 0; i < this->tileList.size(); i++)
	{
		this->tileList.at(i).draw(graphics);
	}

	/*
	SDL_Rect sourceRect = {0, 0, 64, 64};
	SDL_Rect destRect;

	for (int x = 0; x < this->size.x / 64; x++)
	{
		for (int y = 0; y < this->size.y / 64; y++)
		{
			destRect.x = x * 64 * globals::SPRITE_SCALE;
			destRect.y = y * 64 * globals::SPRITE_SCALE;
			destRect.w = 64 * globals::SPRITE_SCALE;
			destRect.h = 64 * globals::SPRITE_SCALE;
			graphics.blitSurface(this->backgroundTexture, &sourceRect, &destRect);
		}
	}
	*/
}