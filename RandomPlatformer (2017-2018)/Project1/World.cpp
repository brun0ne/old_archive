#include "stdafx.h"
#include "World.h"

#include "main.h"

#include <iostream>

void World::addTexture(std::string name, std::string url) {
	sf::Texture t;
	t.loadFromFile(url);

	this->textures.push_back(t);
	this->texture_names.emplace_back(name);
}

sf::Texture & World::texture(std::string name) {
	int i = 0;
	for (auto &t : this->textures) {
		if (this->texture_names[i] == name) {
			return t;
		}
		i++;
	}
}

void World::addObj(float x, float y, float scale, bool collisions, std::string img) {
	this->objects.push_back(Object());

	this->objects.back().Init(x, y, scale, collisions, this->texture(img));
}

void World::objUpdate(sf::RenderWindow & window) {
	for (auto &obj : this->objects) {
		if(player.passRestCollisionTests == false)
			obj.Collisions(this->player);
		obj.Draw(window);
	}
}

void World::addChunk(bool dir) {
	if (dir == true) { // add chunk on right side (from player start point)
		this->chunks.x.push_back(ChunkEl());

		this->chunks.x.back().Generate(this->chunks.x.size() - 1, *this);
	}
	else { // add chunk on left side (from player start point)
		this->chunks.y.push_back(ChunkEl());

		this->chunks.y.back().Generate(- sign(this->chunks.y.size()), *this); // there isn't -1 like in .x loop, because "0" chunk should be only in .x, so +1 is desired
	}
}

void World::chunkUpdate(sf::RenderWindow & window) {
	for (auto &chunk : this->chunks.x) {
		chunk.Draw(window);
	}
	for (auto &chunk : this->chunks.y) {
		chunk.Draw(window);
	}

	// Optimized chunks update ->

	if (this->player.chunk >= 0 && this->chunks.x.size() > 0) { // update only chunk on which player is standing, chunk on left and chunk on right (if p is on .x chunk)
		this->chunks.x[this->player.chunk].Update(window, *this);
		
		if(this->chunks.x.size() > 1)
			this->chunks.x[this->player.chunk + 1].Update(window, *this);

		if(this->player.chunk > 0)
			this->chunks.x[this->player.chunk - 1].Update(window, *this);
		else if(this->chunks.y.size() > 0)
			this->chunks.y[0].Update(window, *this);
	}
	else if (this->player.chunk < 0 && this->chunks.y.size() > 0) { // -||- (if p is on .y chunk)
		int relpos = abs(this->player.chunk + 1);

		this->chunks.y[relpos].Update(window, *this);

		if(this->chunks.y.size() > 1)
			this->chunks.y[relpos + 1].Update(window, *this);

		if (relpos > 0)
			this->chunks.y[relpos - 1].Update(window, *this);
		else if (this->chunks.x.size() > 0)
			this->chunks.x[0].Update(window, *this);
	}
}

void World::infinite(int radius) { // radius defines how away from player new chunks are generated (player as a center, X axis only)
	this->infRadius = radius;
	this->inf = true;

	for (int i = 0; i < radius + 1; i++) { // player is standing on 0 chunk in .x (right from start point), so it should generate one more on the right side
		this->addChunk(true);
	}
	for (int i = 0; i < radius; i++) {
		this->addChunk(false);
	}
}

void World::infiniteUpdate() {
	if (this->player.chunk >= 0 && sign(this->chunks.x.size()) - abs(this->player.chunk) < this->infRadius + 1)  // +1 is here because of -||-
		this->addChunk(true); // add x chunk

	if (this->player.chunk < 0 && sign(this->chunks.y.size()) - abs(this->player.chunk) < this->infRadius)
		this->addChunk(false); // add y chunk
}

void World::Update(sf::RenderWindow & window, sf::View & view) {
	player.falling = true;

	player.passRestCollisionTests = false;

	if (this->inf) { // inf defines in infinite generation on, it can be turned on by calling infinite()
		this->infiniteUpdate();
	}

	this->chunkUpdate(window);

	this->objUpdate(window);

	player.Update(window, view);

	player.pushed = false;
}

ChunkEl World::lastChunk(int pos) {
	if (pos >= 0)
		return this->chunks.x[chunks.x.size()-1-1]; // it actually returns one-before-last chunk, because it is used in chunk gen. when one chunk is just added
	else
		return this->chunks.y[chunks.y.size()-1-1];
}