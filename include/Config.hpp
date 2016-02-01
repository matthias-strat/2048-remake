#pragma once

#include <json/json.h>
#include "Common.hpp"

// Simple configuration class.
class Config
{
public:
    unsigned int getWindowWidth() const noexcept;
    unsigned int getWindowHeight() const noexcept;
    std::string getSchemeFile() const noexcept;

    void loadFromJson(Json::Value& root);
    std::string saveToJson();

private:
    unsigned int m_WindowWidth{defaultWindowWidth};
    unsigned int m_WindowHeight{defaultWindowHeight};
    std::string m_SchemeFile{defaultScheme};
};