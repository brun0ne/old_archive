#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class Missile
{
public:
	Missile(int id);

	int getPosByID(std::vector <Missile> & missiles);

	void Set(float moveX, float moveY, sf::Texture & texture, sf::Vector2f playerPos);

	void Update(sf::RenderWindow & window);

	~Missile() = default;

	bool vis{ false };

	int id{ 0 };

	float g{ 0.1f };

	float friction{ 0 };

	sf::Sprite sprite;

	sf::Vector2f movement{0, 0};
};