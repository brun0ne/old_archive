#include "main.h"
#include "stdafx.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "Player.h"
#include "Object.h"
#include "Enemy.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

void Start(sf::RenderWindow & window) {

}

void Update(sf::Event event, sf::RenderWindow & window, sf::View & view, World & world) {
	world.Update(window, view);
}

int sign(unsigned int x){ // convert unsigned int to signed
	if (x <= INT_MAX)
		return static_cast<int>(x);
	
	if (x >= INT_MIN)
		return static_cast<int>(x - INT_MIN) + INT_MIN;

	throw x;
}

int rand_weight(int choises, std::vector <int> weights) {
	int sum = 0;

	for (auto &weight : weights) {
		sum += weight;
	}

	int rnd = rand() % sum;

	for (int i = 0; i < choises; i++) {
		if (rnd < weights[i])
			return i;
		rnd -= weights[i];
	}

	return 0; // error
}

int game(int seed) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Project1 (codename)");
	//window.setFramerateLimit(60);

	sf::Event event;

	sf::View view(sf::FloatRect(0, 0, 800, 600));

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	World world;

	world.player.Teleport(100, 250);

	world.addTexture("ground1", "graphics/buildings/ground1.png");

	world.addTexture("tree1", "graphics/buildings/Tree1.png");
	world.addTexture("tree2", "graphics/buildings/Tree2.png");

	world.addTexture("house1", "graphics/buildings/shortHouse1.png");
	world.addTexture("house2", "graphics/buildings/shortHouse2.png");

	world.addTexture("enemy1_right", "graphics/enemy1_right.png");
	world.addTexture("enemy1_left", "graphics/enemy1_left.png");
	world.addTexture("enemy1_dmg", "graphics/enemy1_dmg.png");

	world.player.addMissileTexture("missile1", "graphics/canons/canon_start.png");

	if (seed == 0) {
		srand(seed = sign(time(NULL))); // use time as seed

		std::ofstream seedFile;
		seedFile.open("lastseed.txt");
		seedFile << seed; // save seed to file
		seedFile.close();
	}
	else
		srand(seed); // use seed passed from main()

	std::cout << "Using seed: " << seed << "\n";

	world.infinite(3);
	
	/*world.addObj(0, 100, 1, true, "house1");
	world.addObj(400, 100, 1, true, "house1");

	Enemy enemy(450, 50, { 2, 2 }, { 450, 600 }, world.texture("enemy1"));*/

	Start(window);

	while (window.isOpen()) {
		while (accumulator > ups) {
			accumulator -= ups;

			window.clear(sf::Color::White);

			window.pollEvent(event);

			window.setView(view);

			view.setCenter(world.player.sprite.getPosition());

			Update(event, window, view, world);

			/*enemy.Approach(world.player.getCenter(), 500);
			enemy.Update(world.player);
			enemy.Draw(window);*/

			if (event.type == sf::Event::Closed) { // window close
				window.close();

				break;
			}
			else if (event.type == sf::Event::MouseWheelMoved) // zooming (by scroll)
			{
				if (event.mouseWheel.delta > 0)
					view.zoom(1.1f);
				else
					view.zoom(0.9f);
			}

			if (event.type == sf::Event::Resized || sf::Mouse::isButtonPressed(sf::Mouse::Middle)) { // reset view to window's size (on resize / mouse-middle click)
				float w = static_cast<float>(window.getSize().x);
				float h = static_cast<float>(window.getSize().y);

				window.setView(view = sf::View(sf::FloatRect(0, 0, w, h)));
				view.setCenter(world.player.sprite.getPosition());
			}

			window.display();
		}

		accumulator += clock.restart();
	}

	return 0;
}