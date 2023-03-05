#include "stdafx.h"
#include "Object.h"

#include <iostream>

void Object::Init(float x, float y, float scale, bool collisions, sf::Texture & texture) {
	this->sprite.setPosition(x, y);
	this->sprite.setScale(sf::Vector2f(scale, scale));

	this->sprite.setOrigin(this->w / 2, this->h / 2);

	this->sprite.setTexture(texture);

	this->collisions = collisions;
}

void Object::Draw(sf::RenderWindow & window) {
	window.draw(this->sprite);
}

bool Object::Colliding(sf::Sprite sprite) {
	if (this->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		return true;
	else
		return false;
}

float px, py, pw{ 0 }, ph, ox, oy, ow, oh;
bool bounced{ false };

bool Object::Collisions(Player & player) {
	if (this->collisions == false)
		return false;

	px = player.sprite.getGlobalBounds().left;
	py = player.sprite.getGlobalBounds().top;

	ox = this->sprite.getGlobalBounds().left + this->collisionPosisionOffset.x;
	oy = this->sprite.getGlobalBounds().top + this->collisionPosisionOffset.y;

	if (pw == 0) {
		pw = player.sprite.getGlobalBounds().width;
		ph = player.sprite.getGlobalBounds().height;
	}
	if (this->w == 0) {
		this->w = this->sprite.getGlobalBounds().width;
		this->h = this->sprite.getGlobalBounds().height;
	}

	ow = this->w + this->collisionSizeOffset.x;
	oh = this->h + this->collisionSizeOffset.y;

	bounced = false;

	if (px + pw > ox && px < ox + ow && py < oy + oh && py + ph > oy) { // collision check
		player.falling = false; // if something collides, player should stop falling

		if (px + pw > ox + 5 && px < ox + ow - 5) {
			if (py + ph > oy + 0.1f && py < oy + oh / 2) { // bottom
				player.sprite.move(0, oy - (py + ph)); // this get player out of object, for ex. after collision with very high speed
			}

			//std::cout << -player.movement.y << "\n";

			if (player.movement.y < 0) { // top
				player.sprite.move(0, -player.movement.y); // bounce player from the wall

				player.falling = true; // but if its his top wall, he should fall
				player.jumping = false; // and stop accelerating upwards (jumping)

				player.jumpClock = player.mJumpClock;
				player.movement.y = -player.movement.y / player.velDivider; // velDivider defines lost of player's velocity after elastic collision
				bounced = true; // player bounced, movement is reversed, so this protect from later error
				
				player.passRestCollisionTests = true; // player bounced, movement is reversed, so this protect from later error
			}
		}

		else if (py + ph > oy + 5 && py < oy + oh - 5) { // left & right
			player.sprite.move(-player.movement.x, 0);

			player.falling = true; // if it's collision in X axis, player should fall
		}
	}

	if (py + ph > oy && py < oy + oh && px + pw > ox + 5 && px < ox + ow - 5 && player.jumping == false) { // collisions on Y axis (bottom)
		if (player.movement.y >= 0 && bounced == false) { // bottom
			player.falling = false; // player shouldn't fall

			if (abs(-player.movement.y / player.velDivider) > 1.0f) {
				player.movement.y = -player.movement.y / player.velDivider; // velDivider defines lost of player's velocity after elastic collision

				player.passRestCollisionTests = true; // player bounced, movement is reversed, so this protect from later error
			}
			else {
				player.movement.y = 0; // if rebounce speed is realy low, player shouldn't bouce
			}
		}
	}

	return true;
}

bool Object::setCollisionOffset(float x, float y, float w, float h) {
	this->collisionPosisionOffset.x = x;
	this->collisionPosisionOffset.y = y;
	
	this->collisionSizeOffset.x = w;
	this->collisionSizeOffset.y = h;

	return true;
}

bool Object::missileCollisions(Player & player) {
	if (this->collisions == false)
		return false;

	int i = 0;

	for (auto & missile : player.missiles) { // for every missile
		if (this->Colliding(missile.sprite)) { // if collides
			if (!player.missiles.empty())
				player.missiles.erase(player.missiles.begin() + i);
		}
		else if (missile.sprite.getGlobalBounds().top > 1500) { // maximum y of missile
			if (!player.missiles.empty())
				player.missiles.erase(player.missiles.begin() + i);
		}
		else
			i++;
	}

	return true;
}