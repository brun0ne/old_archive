#pragma once

#include <SFML/Graphics.hpp>
#include "Missile.h"
#include "Stats.h"

class Player
{
public:
	Stats stats;

	Player(float x, float y);

	~Player() = default;

	void Gravity();

	void Update(sf::RenderWindow & window, sf::View & view);

	sf::Vector2f getCenter();

	// Interactions - >

	bool Push(float velX, float velY);

	bool Teleport(float x, float y);

	// <-

	// Missiles - >

	void addMissileTexture(std::string name, std::string url);

	sf::Texture & getMissileTexture(std::string name);

	void addMissile(float moveX, float moveY, std::string textureName);

	void missilesUpdate(sf::RenderWindow & window);

	// <-

	sf::Vector2f velocity{ 4.0f, 1.5f }; // velocity: x - walking, y - jumping
	sf::Vector2f movement{ 0.0f, 0.0f };

	sf::Sprite sprite;

	bool falling{ true };
	bool jumping{ false };
	bool pushed{ false };

	int chunk{ 0 }; // defines on which chunk player is standing

	int jumpClock{ 0 };

	bool passRestCollisionTests{ false };

	std::string dir{ "down" }; // player direction

	float velDivider{ 3 }; // velDivider defines lost of player's velocity after elastic collision

	int mJumpClock{ 3 }; // mJumpClock defines how long player is accelerating while jumping
	float mass{ 1 }; // mass increase g and jump time (proportionally) 

	// Missiles (variables) ->

	std::vector < Missile > missiles;
	std::vector < sf::Texture > missile_textures;
	std::vector < std::string > missile_texture_names;

	int missile_clock{ 0 };
	float missile_cooldown{ 0.5f }; // defines cooldown (in seconds)

	int damaged_clock{ 0 };
	float damaged_cooldown{ 0.5f }; // (seconds)

	int missileID_iterator{ 0 };

	std::string actmissilename{ "missile1" };

	bool right_hold{ false }; // right mouse button hold

	// <-

private:
	sf::Texture texture [5];

	float g{ 0.1f }; // g is falling acceleration
};