#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Stats.h"

class Enemy
{
public:
	Stats stats;

	Enemy(float x, float y, sf::Vector2f speed, sf::Vector2f minMaxX);

	void setStats(float strengh /* ... */);

	~Enemy() = default;

	void Draw(sf::RenderWindow & window);

	void Update(Player & player);

	void setRoute(float x1, float x2, float y1, float y2);

	void Approach(Player * player, float radius); // dirs defines axis of movement

	bool Colliding(sf::Sprite sprite);
	bool Collisions(Player & player);

	void upTextureSet(); // make shure that enemy has a texture

	// Interactions ->

	void giveDamage(Player & player);
	void dealDamage(Player & player);

	// <-

	std::string facing = "";

	bool routing{ false };
	bool approaching{ false };

	float approachRadius{ 0 };

	sf::Texture textures[3];

	sf::Vector2f speed{ 0, 0 };

	sf::Vector2f initialPos{ 0, 0 };

	sf::Vector2 < bool > dir{ true, true }; // true - right, down ; false - left, up

	sf::Sprite sprite;

	sf::Vector2f movement{ 0, 0 };

	sf::Vector2f routeX{ 0, 0 };
	sf::Vector2f routeY{ 0, 0 };

	//sf::Vector2f approachPos{ 0, 0 };
	Player * approachPlayer;

	sf::Vector2f minMaxX{ 0, 0 }; // platform begin and end, use while approaching

	int damaged_clock{ 0 };
	float damaged_cooldown{ 0.5f }; // (seconds)

	bool active{ false };
};