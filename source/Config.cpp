#include "Config.hpp"

unsigned int Config::getWindowWidth() const noexcept { return m_WindowWidth; }
unsigned int Config::getWindowHeight() const noexcept { return m_WindowHeight; }
unsigned int Config::getFullscreenWidth() const noexcept { return m_FullscreenWidth; }
unsigned int Config::getFullscreenHeight() const noexcept { return m_FullscreenHeight; }
bool Config::getFullscreen() const noexcept { return m_Fullscreen; }