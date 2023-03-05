#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>

class Textures {
public:
	Textures() = default;

	void load();

	sf::Texture house1;
};