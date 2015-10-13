#pragma once

#include "ResourceHolder.hpp"

// This file contains strongly typed enums to identify the managed sfml resources in the memory and thus make them re-usable.

enum class Textures
{
	Resize,
	Menu,
	MenuButton,
	Tiles,
	Grid,
};

enum class Fonts
{
	Verdana
};

using FontHolder	= ResourceHolder<sf::Font, Fonts>;
using TextureHolder = ResourceHolder<sf::Texture, Textures>;