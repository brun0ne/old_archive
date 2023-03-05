#pragma once

#include "stdafx.h"

#include "World.h"

class World; // forward declaration

class ChunkEl
{
public:
	ChunkEl() = default;

	~ChunkEl() = default;

	ChunkEl left(World & world); // returns chunk which is on the left from this chunk (in world)
	ChunkEl right(World & world); // vice-versa

	void addObj(float x, float y, float scale, bool collisions, sf::Vector2 <int> cut, sf::Vector2 <int> cutStartCorner, std::string img, World & world);

	void Generate(int pos, World & world);

	void Update(sf::RenderWindow & window, World & world);

	void Draw(sf::RenderWindow & window);

	int position{ 0 };

	int mainY{ 500 };

	// left wall of chunk (world's absolute): this->position * world.chunkWidth
	// right wall of chunk (world's absolute): this->position * world.chunkWidth + world.chunkWidth
	
private:

	std::vector < Object > objects;

	std::vector < Enemy > enemies;
};