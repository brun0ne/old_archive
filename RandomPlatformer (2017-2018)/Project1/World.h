#pragma once

#include "stdafx.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Enemy.h"

#include "ChunkEl.h"

class ChunkEl; // forward declaration

class World
{
public:
	World() = default;

	void addTexture(std::string name, std::string url);
	sf::Texture & texture(std::string url);

	void addObj(float x, float y, float scale, bool collisions, std::string img);

	void objUpdate(sf::RenderWindow & window);

	void addChunk(bool dir);

	void chunkUpdate(sf::RenderWindow & window);

	void infinite(int radius);

	void Update(sf::RenderWindow & window, sf::View & view);

	ChunkEl lastChunk(int pos); // pos of requesting chunk

	~World() = default;

	Player player{0, 0};

	const int chunkWidth{ 1000 }; // defines width of all chunks

	sf::Vector2 < std::vector < ChunkEl > > chunks; // vector2 of vectors.. of chunks. yeah. x is for "-" pos chunks (left from player's start point) and vice-versa for y

private:
	std::vector < Object > objects;
	std::vector < sf::Texture > textures;
	std::vector < std::string > texture_names;

	int infRadius{ 0 };
	bool inf{ false };

	void infiniteUpdate();
};