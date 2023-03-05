#include "stdafx.h"

#include "Player.h"

#include <iostream>

#define PI 3.14159265

#define Player_W 50
#define Player_H 50

Player::Player(float x, float y) : stats(100, 10, 5)
{
	this->texture[0].loadFromFile("graphics/player/player.png", sf::IntRect(0, 0, 50, 50)); // down / idle
	this->texture[1].loadFromFile("graphics/player/player.png", sf::IntRect(50, 0, 50, 50)); // up
	this->texture[2].loadFromFile("graphics/player/player.png", sf::IntRect(100, 0, 50, 50)); // left
	this->texture[3].loadFromFile("graphics/player/player.png", sf::IntRect(150, 0, 50, 50)); // right
	this->texture[4].loadFromFile("graphics/player/player.png", sf::IntRect(200, 0, 50, 50)); // damage

	this->sprite.setTexture(this->texture[0]); // idle

	sprite.setPosition(x, y); // position
	sprite.setOrigin(25, 25); // origin (center)

}

void Player::Gravity() {
	if (this->falling) {
		this->movement.y += g * mass; // g is falling acceleration
	}
	if (this->jumping) {
		this->movement.y += -this->velocity.y; // velocity.y is jumping velocity
	}

	if (this->jumping)
		this->jumpClock++;
	if (this->jumpClock == this->mJumpClock) { // mJumpClock defines how long player is accelerating while jumping (define in .h)
		this->jumping = false;
		this->jumpClock = 0;
	}

	//std::cout << "Player v(y) = " << static_cast<int>(this->movement.y) << "\n";
	//std::cout << this->movement.y << "\n";
}

void Player::Update(sf::RenderWindow &window, sf::View & view) {
	this->Gravity();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->falling == false && this->jumping == false) { // jumping
		this->jumping = true;
	}

	// DAMAGE ->

	bool damaged = false;

	if (damaged_clock > 0) {
		damaged = true;
		
		if (this->dir != "dmg") {
			this->sprite.setTexture(this->texture[4]);
			this->dir = "dmg";
		}

		damaged_clock--;
	}
	else if (this->dir == "dmg") {
		this->sprite.setTexture(this->texture[0]);
		this->dir = "down";
	}

	// <-

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // facing downwards; no movement
		if (this->dir != "down" && damaged == false) {
			this->sprite.setTexture(this->texture[0]);

			this->dir = "down";
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && this->jumping == false) { // for test/debug purposes only
		this->Push(0, -10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // moving left
		this->movement.x = -velocity.x;
		
		if (this->dir != "left" && damaged == false) {
			this->sprite.setTexture(this->texture[2]);

			this->dir = "left";
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // moving right
		this->movement.x = velocity.x;

		if (this->dir != "right" && damaged == false) {
			this->sprite.setTexture(this->texture[3]);

			this->dir = "right";
		}
	}
	else {
		this->movement.x = 0;
	}

	this->missilesUpdate(window); // missiles

	window.draw(this->sprite); // drawing

	this->sprite.move(this->movement); // moving
}

sf::Vector2f Player::getCenter() {
	return {this->sprite.getGlobalBounds().left + (Player_W / 2), this->sprite.getGlobalBounds().top + (Player_H / 2)};
}

// Interactions ->

bool Player::Push(float velX, float velY) {
	if(abs(velY) > 0)
		this->jumping = true; // prevent bugs

	this->movement.x = velX;
	this->movement.y = velY;

	this->pushed = true;

	return true;
}

bool Player::Teleport(float x, float y) {
	this->sprite.setPosition(x, y);

	return true;
}

// <-

// Missiles ->

void Player::addMissileTexture(std::string name, std::string url) {
	sf::Texture t;
	t.loadFromFile(url);

	this->missile_textures.push_back(t);
	this->missile_texture_names.emplace_back(name);
}

sf::Texture & Player::getMissileTexture(std::string name) {
	int i = 0;
	for (auto &t : this->missile_textures) {
		if (this->missile_texture_names[i] == name) {
			return t;
		}
		i++;
	}
}

void Player::addMissile(float moveX, float moveY, std::string textureName) {
	this->missiles.emplace_back(Missile(this->missileID_iterator));

	this->missileID_iterator++;

	this->missiles.back().Set(moveX, moveY, this->getMissileTexture(textureName), sf::Vector2f{this->sprite.getGlobalBounds().left, this->sprite.getGlobalBounds().top});
}

void Player::missilesUpdate(sf::RenderWindow & window) {
	if (missile_clock > 0)
		missile_clock--;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->missile_clock == 0) {
			const sf::Vector2i mousepos = sf::Mouse::getPosition(window);

			const sf::Vector2f delta = { (float)(mousepos.x - window.mapCoordsToPixel(this->sprite.getPosition()).x), (float)(mousepos.y - window.mapCoordsToPixel(this->sprite.getPosition()).y) };

			float angle = atan2(delta.y, delta.x);

			float Ycor = delta.x / 100;

			this->addMissile(cos(angle) * 10 + this->movement.x, sin(angle) * 10 + this->movement.y, this->actmissilename);

			missile_clock = (int)(missile_cooldown * 60);
		}
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (!this->right_hold) {
			// HOLD starts

			this->right_hold = true;
		}

		// HOLD update

		const sf::Color color = sf::Color::Black;

		const sf::Vector2i mousepos = sf::Mouse::getPosition(window);

		sf::Vertex line[] = {
			sf::Vertex(sprite.getPosition(), color),
			sf::Vertex(sf::Vector2f(window.mapPixelToCoords(mousepos)), color)
		};

		window.draw(line, 2, sf::Lines);//
	}
	else if (this->right_hold) {
		// HOLD ends

		

		this->right_hold = false;
	}

	for (auto & missile : this->missiles) { // for every missile
		missile.Update(window);
	}
}

// <-