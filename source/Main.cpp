#include "Game.hpp"

bool loadConfigFile(const std::string& filename, Json::Value& root)
{

    return true;
}

int main()
{
    Json::Value configRoot;
    if (!loadConfigFile("config.json", configRoot))
    {
        std::cerr << "Failed to load configuration file." << std::endl;
        return 1;
    }

    Config config;
    config.loadFromJson(configRoot);

    std::cout << "schemeFile = " << config.getSchemeFile() << std::endl;

    Game{}.run();
    return 0;
}
