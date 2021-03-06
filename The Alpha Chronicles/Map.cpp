#include "Map.h"
#include <iostream>

Map::Map() {
	int mapWidth, mapHeight, tileID;
	sf::IntRect tileRects[3];
	tileRects[0] = sf::IntRect(32, 352, 32, 32);
	tileRects[1] = sf::IntRect(128, 544, 32, 32);

	std::ifstream mapFile;
	mapFile.open("res/maps/map1.map");
	mapFile >> mapWidth >> mapHeight;
	
	bool solid = false;

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			mapFile >> tileID;
			(tileID == 1 ? solid = true : solid = false); //temporary, make tiles with ID 1 solid and others not solid
			tiles.push_back(Tile(tileRects[tileID], sf::Vector2f(x * 32.0f, y * 32.0f), solid));
		}
	}

	width = mapWidth * 32;
	height = mapHeight * 32;

	tileMap.loadFromFile("res/terrain.png");
}

Map::~Map() {

}

void Map::tick() {
	
}

void Map::render(sf::RenderWindow* window, int xOffset, int yOffset) {

	currentTile.setTexture(tileMap);
	for (int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i).getLocation().x > (xOffset - 32) && tiles.at(i).getLocation().y > (yOffset - 32) &&
			tiles.at(i).getLocation().x < (xOffset + window->getSize().x) && tiles.at(i).getLocation().y < (yOffset + window->getSize().y)) {
			currentTile.setTextureRect(tiles.at(i).getTextureRect());
			currentTile.setPosition(sf::Vector2f(tiles.at(i).getLocation().x - xOffset, tiles.at(i).getLocation().y - yOffset));

			window->draw(currentTile);
		}
	}
}

Tile Map::getTile(float x, float y) {
	sf::IntRect currentTile;
	for (int i = 0; i < tiles.size(); i++) {
		currentTile = tiles.at(i).getRect();
		if (currentTile.contains(sf::Vector2i((int)x, (int)y))) {
			return tiles.at(i);
		}
	}

	return Tile();
}

int Map::getWidth() {
	return width;
}

int Map::getHeight() {
	return height;
}