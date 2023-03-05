#include "stdafx.h"
#include "ChunkEl.h"
#include "main.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

ChunkEl ChunkEl::left(World & world) {
	if (this->position > 0)
		return world.chunks.x[this->position - 1];
	else if(this->position < 0)
		return world.chunks.y[abs(this->position)];
	else
		return world.chunks.y[this->position]; // there is nothing on the left in .x, so it returns first element of .y
}

ChunkEl ChunkEl::right(World & world) {
	if (this->position > 0)
		return world.chunks.x[this->position + 1];
	else if (this->position < -1)
		return world.chunks.y[abs(this->position) - 2];
	else if (this->position == -1)
		return world.chunks.x[abs(this->position) - 1]; // there is nothing on the right in .y, so it returns fisrt element of .x
}

void ChunkEl::addObj(float x, float y, float scale, bool collisions, sf::Vector2 <int> cut, sf::Vector2 <int> cutStartCorner, std::string img, World & world) {
	this->objects.push_back(Object());

	if (cut.x == 0 && cut.y == 0) {
		this->objects.back().Init(x, y, scale, collisions, world.texture(img));
	}
	else {
		this->objects.back().Init(x, y, scale, collisions, world.texture(img));
		this->objects.back().sprite.setTextureRect(sf::IntRect(0, 0, cut.x, cut.y));
	}
}

std::vector <std::string> treeTextures = { "tree1", "tree2" };
std::vector <float> treeScales = { 0.3f, 0.8f };
std::vector <int> treeRarity = {2, 1};

void ChunkEl::Generate(int pos, World & world) {

	// Platforms ->

	int offsetY{ 0 }, allW{ 0 }, allGap{ 0 };

	std::vector <int> width;
	std::vector <int> gap;

	if (pos != 0 && pos != -1) // if it isn't first chunk in a vector
		this->mainY = world.lastChunk(pos).mainY + rand() % 100 - 50; // main y is shifted by -50 to 50 // !!! something isn't working here

	while (allW + allGap < world.chunkWidth) {
		width.emplace_back( rand() % (world.chunkWidth - 200) + 200 ); // 200 to chunkWidth
		gap.emplace_back(rand() % 50 + 50); // 50 to 100
		
		allW += width.back();
		allGap += gap.back();

		if (allW + allGap > world.chunkWidth) {
			int devide = ((allW + allGap) - world.chunkWidth) + (rand() % 50 + 50);

			width.back() -= devide;
			allW -= devide;

			if (width.back() < 200) { // minimum platform length
				allW -= width.back();
				allGap -= gap.back();

				width.pop_back();
				gap.pop_back();
			}

			break;
		}
	}

	int offsetX{ 0 };

	for (unsigned int i = 0; i < width.size(); i++) { // for every platform
		if (i != 0)
			offsetX += gap[i - 1];

		this->addObj(world.chunkWidth * pos + offsetX, this->mainY + (rand() % 100 - 50), 1, true, { width[i], 104 }, { 0, 0 }, "ground1", world);
		this->objects.back().setCollisionOffset(0, 0, 0, 0);

		offsetX += width[i];
	}

	// <-

	// Trees ->

	allW = 0;
	allGap = 0;

	offsetX = 0;

	width.empty();
	gap.empty();

	std::vector <Object> platforms = this->objects;

	int px, py, pw, ph, add, startpos, r;
	float actscale;

	for (auto &platform : platforms) { // for every platform
		px = platform.sprite.getGlobalBounds().left;
		py = platform.sprite.getGlobalBounds().top;
		pw = platform.sprite.getGlobalBounds().width;
		ph = platform.sprite.getGlobalBounds().height;

		startpos = (rand() % 200 + 50); // first tree on every platform shouldn't be always in the same spot

		if (startpos > pw)
			startpos -= pw;

		offsetX += startpos;
		allW += startpos;

		while (allW < pw) {
			r = rand_weight(treeTextures.size(), treeRarity); // pick a random tree (including rarity)

			actscale = treeScales[r] + (float)( (float)(rand() % 10 - 5) / (float)100); // scale +- 0.2

			if (allW + sign(world.texture(treeTextures[r]).getSize().x) * actscale > pw) // if another tree won't fit - break
				break;

			this->addObj(px + offsetX, py - sign(world.texture(treeTextures[r]).getSize().y) * actscale, actscale, false, { 0, 0 }, { 0, 0 }, treeTextures[r], world);

			std::cout << this->mainY << "\n";

			add = sign(world.texture(treeTextures[r]).getSize().x) * actscale + (rand() % 200 + 50);

			offsetX += add;
			allW += add;
		}
	}

	// <-

	// Enemies ->

	for (auto &platform : platforms) { // for every platform
		int rander = rand() % 100;

		if (rander > 50) // chance 1 in 10 for monster spawn on a platform
			continue;

		px = platform.sprite.getGlobalBounds().left;
		py = platform.sprite.getGlobalBounds().top;
		pw = platform.sprite.getGlobalBounds().width;
		ph = platform.sprite.getGlobalBounds().height;

		int eX = rand() % pw + px;
		int eY = py - 50;

		this->enemies.push_back( Enemy( eX, eY, {1.5f, 1.f}, { float(px), float(px + pw) } ) );

		this->enemies.back().setRoute(float(px), float(px + pw), 0, 0);

		this->enemies.back().textures[0] = world.texture("enemy1_right");
		this->enemies.back().textures[1] = world.texture("enemy1_left");
		this->enemies.back().textures[2] = world.texture("enemy1_dmg");
	}

	// <-

	this->position = pos;
}

void ChunkEl::Update(sf::RenderWindow & window, World & world) {
	for (auto &obj : this->objects) {
		obj.Collisions(world.player);
		obj.missileCollisions(world.player);
	}

	int i = 0;

	for (auto &enemy : this->enemies) {
		enemy.Update(world.player);
		enemy.Draw(window);

		if (enemy.stats.HP <= 0) { // death
			enemies.erase(enemies.begin() + i);
		}
		i++;
		//enemy.Approach(world.player.getCenter(), 500);
	}

	if (world.player.sprite.getPosition().x + 50 > this->position * world.chunkWidth && world.player.sprite.getPosition().x < this->position * world.chunkWidth + world.chunkWidth) {
		// if player gets into this chunk, set his "chunk" parameter to position of this chunk

		if (world.player.chunk != this->position) {
			world.player.chunk = this->position;
		}
	}
}

void ChunkEl::Draw(sf::RenderWindow & window) {
	for (auto &obj : this->objects) {
		obj.Draw(window);
	}
	/*for (auto &enemy : this->enemies) {
		enemy.Draw(window);
	}*/
}