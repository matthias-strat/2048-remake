#pragma once

#include <json/json.h>

#include "Common.hpp"
#include "Config.hpp"

class Assets
{
public:
    Assets(Config& config);
    Assets(const Assets&) = delete;
    Assets& operator=(const Assets&) = delete;

    void load();
    sf::IntRect getTileTextureRect(int value) const;

public:
    // Max supported tile (2^19 = 524288)
    static constexpr int maxTileIndex{19};

    // Fonts
    sf::Font fntCode;
    sf::Font fntSansation;

    // Textures
    sf::Texture txCursor;
    sf::Texture txRoundedRect;
    sf::Texture txRoundedRectSmall;
    const sf::Texture* txGrid{nullptr};
    const sf::Texture* txTile{nullptr};
    const sf::Texture* txScoreboard{nullptr};

    // Colors (TODO: Load from scheme file)
    sf::Color colBackground{250, 248, 239};
    sf::Color colGrid{187, 173, 160};
    sf::Color colGridCell{205, 192, 180};
    sf::Color colTiles[maxTileIndex] // idx 0 = 2, idx 1 = 4, idx 2 = 8, ...
    {
        {238, 228, 218},    // 2
        {237, 224, 200},    // 4
        {242, 177, 121},    // 8
        {245, 149, 99},     // 16
        {246, 124, 95},     // 32
        {246, 94, 59},      // 64
        {237, 207, 114},    // 128
        {237, 204, 97},     // 256
        {237, 200, 80},     // 512
        {237, 197, 63},     // 1024
        {237, 194, 46},     // 2048
        {63, 58, 50},       // 4096
        {63, 58, 50},       // 8192
        {63, 58, 50},       // 16384
        {63, 58, 50},       // 32768
        {63, 58, 50},       // 65536
        {63, 58, 50},       // 131072
        {63, 58, 50},       // 262144
        {63, 58, 50}        // 524288
    };
    sf::Color colTilesFont[maxTileIndex]
    {
        {119, 110, 101},    // 2
        {119, 110, 101},    // 4
        {249, 246, 242},    // 8
        {249, 246, 242},    // 16
        {249, 246, 242},    // 32
        {249, 246, 242},    // 64
        {249, 246, 242},    // 128
        {249, 246, 242},    // 256
        {249, 246, 242},    // 512
        {249, 246, 242},    // 1024
        {249, 246, 242},    // 2048
        {249, 246, 242},    // 4096
        {249, 246, 242},    // 8192
        {249, 246, 242},    // 16384
        {249, 246, 242},    // 32768
        {249, 246, 242},    // 65536
        {249, 246, 242},    // 131072
        {249, 246, 242},    // 262144
        {249, 246, 242}     // 524288
    };

    sf::Color colTxtScore{187, 173, 160};

private:
    void createGridTexture();
    void createTileTextures();
    void createScoreTexture();

    void loadSchemeFromJson(const Json::Value& root);

    UPtr<sf::RenderTexture> m_GridRender;
    UPtr<sf::RenderTexture> m_TileRender;
    UPtr<sf::RenderTexture> m_ScoreRender;

    Config& m_Config;
};
