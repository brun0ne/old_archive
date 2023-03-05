#include "stdafx.h"
#include "Missile.h"

#include <iostream>

Missile::Missile(int id){
	this->id = id;
}

int Missile::getPosByID(std::vector <Missile> & missiles) {
	for (int i = 0; i < missiles.size(); i++) { // for every missile
		if (missiles[i].id == this->id) {
			return i;
		}
	}

	return 0; // error
}

void Missile::Set(float moveX, float moveY, sf::Texture & texture, sf::Vector2f playerPos) {
	this->vis = true;

	this->movement = {moveX, moveY};

	this->sprite.setTexture(texture);
	this->sprite.setScale(0.3f, 0.3f);

	this->sprite.setPosition(playerPos);
}

void Missile::Update(sf::RenderWindow & window) {
	this->movement.y += g;

	if(this->movement.x > 0)
		this->movement.x -= friction;

	this->sprite.move(this->movement);

	if(vis)
		window.draw(this->sprite);
}