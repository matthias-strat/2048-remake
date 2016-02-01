#include "Config.hpp"
#include <json/json.h>

unsigned int Config::getWindowWidth() const noexcept
{
    return m_WindowWidth;
}

unsigned int Config::getWindowHeight() const noexcept
{
    return m_WindowHeight;
}

std::string Config::getSchemeFile() const noexcept
{
    return m_SchemeFile;
}

void Config::loadFromJson(Json::Value& root)
{
    m_WindowWidth = root.get("window_width", defaultWindowWidth).asUInt();
    m_WindowHeight = root.get("window_height", defaultWindowHeight).asUInt();
    m_SchemeFile = root.get("scheme_file", defaultScheme).asString();
}