#include "stdafx.h"
#include "Enemy.h"
#include <iostream>

#define enemySize 50

Enemy::Enemy(float x, float y, sf::Vector2f speed, sf::Vector2f minMaxX) : stats(50, 5, 2){
	this->sprite.setPosition(x, y);
	
	this->initialPos = { x, y };

	this->speed = speed;

	this->minMaxX = minMaxX;
}

void Enemy::setStats(float strengh /* ... */) {
	this->stats.strengh = strengh;
	// ...
}

void Enemy::Draw(sf::RenderWindow & window) {
	window.draw(this->sprite);
}

void Enemy::upTextureSet() {
	if (this->sprite.getTexture() == NULL) {
		this->sprite.setTexture(this->textures[0]);
	}
}

void Enemy::Update(Player & player) {

	// DMG texture ->

	bool damaged = false;
	if (damaged_clock > 0) {
		damaged = true;

		if (this->facing != "dmg") {
			this->sprite.setTexture(this->textures[2]);
			this->facing = "dmg";
		}

		damaged_clock--;
	}
	else if (this->facing == "dmg") {
		if (player.getCenter().x > this->sprite.getGlobalBounds().left + enemySize / 2) { // right
			this->facing = "right";

			this->sprite.setTexture(this->textures[0]);
		}
		else { // left
			this->facing = "left";

			this->sprite.setTexture(this->textures[1]);
		}
	}

	// <-

	// Routing ->

	if (this->routing == true) {
		// turning after passing a distance from initial position
		
		if (this->routeX.x != 0 || this->routeX.y != 0) {
			if (this->sprite.getGlobalBounds().left < this->routeX.x)
				this->dir.x = true; // right

			if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width > this->routeX.y)
				this->dir.x = false; // left

			// set movement

			if (this->dir.x == true) {
				// right
				this->movement.x = this->speed.x;

				if (this->facing != "right" && !damaged) {
					this->sprite.setTexture(this->textures[0]);
					this->facing = "right";
				}
			}
			else {
				// left
				this->movement.x = -this->speed.y;

				if (this->facing != "left" && !damaged) {
					this->sprite.setTexture(this->textures[1]);
					this->facing = "left";
				}
			}
		}
		
		if (this->routeY.x != 0 || this->routeY.y != 0) {
			if (this->sprite.getGlobalBounds().top < this->routeY.x)
				this->dir.y = true; // down

			if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height > this->routeY.y)
				this->dir.y = false; // up

			// set movement

			if (this->dir.y == true) {
				// down
				this->movement.y = this->speed.x;
			}
			else {
				// up
				this->movement.y = -this->speed.y;
			}
		}
	}
	else if (this->approaching == true) {
		sf::Vector2f center{ this->sprite.getGlobalBounds().left + (this->sprite.getGlobalBounds().width / 2), this->sprite.getGlobalBounds().top + (this->sprite.getGlobalBounds().height / 2) };

		if (this->approachPlayer->getCenter().x > this->minMaxX.x - enemySize / 2 && this->approachPlayer->getCenter().x < this->minMaxX.y + enemySize / 2) { // X axis
			if (center.x < this->approachPlayer->getCenter().x && center.x < this->minMaxX.y + enemySize / 2) {
				this->movement.x = this->speed.x; // right

				if (this->facing != "right" && !damaged) {
					this->sprite.setTexture(this->textures[0]);
					this->facing = "right";
				}
			}
			else if (center.x > this->approachPlayer->getCenter().x && center.x > this->minMaxX.x - enemySize / 2) {
				this->movement.x = -this->speed.x; // left

				if (this->facing != "left" && !damaged) {
					this->sprite.setTexture(this->textures[1]);
					this->facing = "left";
				}
			}
			else {
				this->movement.x = 0;
			}

			// minMaxX avoid moving out from platforms
		}
		else {
			this->approaching = false;
			this->routing = true;
			this->active = false;
		}
		
		// approaching in Y axis (flying? jumping?) TODO
	}

	// <-

	this->upTextureSet(); // temporary, without it enemies sometimes glitch

	this->Collisions(player);

	this->sprite.move(this->movement);
}

void Enemy::setRoute(float x1, float x2, float y1, float y2) {
	this->routeX = { x1, x2 };
	this->routeY = { y1, y2 };

	this->routing = true;
	this->approaching = false;
}

void Enemy::Approach(Player * player, float radius) {
	this->approachRadius = radius;
	
	this->approachPlayer = player;

	this->approaching = true;
	this->routing = false;
}

bool Enemy::Colliding(sf::Sprite sprite) {
	if (sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
		return true;
	}
	else
		return false;
}

bool Enemy::Collisions(Player & player) {
	if (this->Colliding(player.sprite)) {
		this->giveDamage(player);
	}

	int i = 0;

	for (auto & missile : player.missiles) { // for every missile
		if (this->Colliding(missile.sprite)) { // if collides
			if (!player.missiles.empty()) {
				player.missiles.erase(player.missiles.begin() + i);

				// damage enemy

				this->dealDamage(player);
			}
		}
		else
			i++;
	}

	return false;
}

// Interactions ->

void Enemy::giveDamage(Player & player) {
	player.stats.HP -= (this->stats.strengh - player.stats.defence);

	player.Push(0, -2);

	player.damaged_clock = player.damaged_cooldown * 60; // for "damaged texture" and invincibility
}

void Enemy::dealDamage(Player & player) {
	this->stats.HP -= (player.stats.strengh - this->stats.defence);

	this->damaged_clock = this->damaged_cooldown * 60; // for "damaged texture"

	if (this->active == false) {
		this->Approach(&player, 500);

		this->active = true;
	}
}

// <-