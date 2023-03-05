#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Object
{
public:
	Object() = default;

	void Init(float x, float y, float scale, bool collisions, sf::Texture & texture);

	~Object() = default;

	void Draw(sf::RenderWindow & window);

	bool Colliding(sf::Sprite sprite);
	bool Collisions(Player & player);
	bool missileCollisions(Player & player);

	float w;
	float h;

	bool collisions{ true };

	bool setCollisionOffset(float x, float y, float w, float h);

	sf::Vector2f collisionPosisionOffset{ 0, 0 };
	sf::Vector2f collisionSizeOffset{0, 0};

	sf::Sprite sprite;
	sf::Texture texture;
};

