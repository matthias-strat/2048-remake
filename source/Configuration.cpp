#include "Pch.hpp"
#include "Configuration.hpp"

const unsigned int Configuration::DefaultVideoWidth{ 1024 };
const unsigned int Configuration::DefaultVideoHeight{ 768 };
const bool Configuration::DefaultVSync{ true };
const unsigned int Configuration::DefaultAntialiasing{ 0 };
const bool Configuration::DefaultShowFps{ false };

Configuration::Configuration(const std::string& filename)
	: m_Filename{filename}
{
	setDefaultValues(false);
}

bool Configuration::load()
{
	return true;
}

bool Configuration::save()
{
	return true;
}

void Configuration::setDefaultValues(bool updated)
{
	m_VideoWidth = DefaultVideoWidth;
	m_VideoHeight = DefaultVideoHeight;
	m_VSync = DefaultVSync;
	m_Antialiasing = DefaultAntialiasing;
	m_ShowFps = DefaultShowFps;
	if (updated) m_WasUpdated = true;
}