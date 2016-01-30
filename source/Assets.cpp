#include "Assets.hpp"
#include "NinePatch.hpp"
#include "Embedded.hpp"

#include <cassert>

namespace
{
    unsigned int getLogBase2(int v) noexcept
    {
        // http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn

        static const int multiplyDeBruijnBitPosition[32] =
            {
                0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
                8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
            };

        int r; // result goes here
        v |= v >> 1; // first round down to one less than a power of 2 
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        r = multiplyDeBruijnBitPosition[v * 0x07C4ACDDU >> 27];
        return r;
    }

    template <typename TFunc, typename... TArgs>
    inline void measureFunction(const std::string& name, const TFunc& func, TArgs&&... args)
    {
        auto tp1(HRClock::now());
        func(FWD(args)...);
        auto tp2(HRClock::now());
        auto elapsedMs(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count());
        std::cout << "Assets::" << name << "() took " << elapsedMs << " ms\n";
    }
}

Assets::Assets(Config& config)
    : m_Config{config}
{
}

void Assets::load()
{
    // Load fonts
    fntCode.loadFromFile("assets/codebd.otf");
    fntSansation.loadFromFile("assets/sansation.ttf");

    // Load nine-patch assets from embedded memory.
    txRoundedRect.loadFromMemory(pngRoundedRect, pngRoundedRectSize);
    txRoundedRectSmall.loadFromMemory(pngRoundedRectSmall, pngRoundedRectSmallSize);

    measureFunction("createGridTexture", [this]() { createGridTexture(); });
    measureFunction("createTileTextures", [this]() { createTileTextures(); });
}

sf::IntRect Assets::getTileTextureRect(int v) const
{
    assert(v % 2 == 0);

    // Calculate position in the tileset (based on v's exponent)
    auto exp(getLogBase2(v) - 1);
    auto x(exp % 5), y(exp / 5);

    return sf::IntRect(x * defaultTileSize, y * defaultTileSize, defaultTileSize, defaultTileSize);
}

void Assets::createGridTexture()
{
    auto size(calculateGridSize(defaultNumCells, defaultTileSize, defaultSpacing));
    m_GridRender = std::make_unique<sf::RenderTexture>();
    m_GridRender->create(size, size);

    sf::RenderStates states;
    states.blendMode = sf::BlendNone;

    // Draw background
    NinePatch np{txRoundedRect,{static_cast<float>(size), static_cast<float>(size)}};
    np.setColor(colGrid);
    m_GridRender->draw(np, states);

    // Draw cells
    np.setTexture(txRoundedRectSmall);
    np.setSize({static_cast<float>(defaultTileSize), static_cast<float>(defaultTileSize)});
    np.setColor(colGridCell);

    float xPos{defaultSpacing}, yPos{defaultSpacing};
    for (auto x(0); x < defaultNumCells; x++)
    {
        for (auto y(0); y < defaultNumCells; y++)
        {
            np.setPosition(xPos, yPos);
            m_GridRender->draw(np);
            yPos += defaultTileSize + defaultSpacing;
        }

        xPos += defaultTileSize + defaultSpacing;
        yPos = defaultSpacing;
    }

    m_GridRender->display();

    txGrid = &m_GridRender->getTexture();
}

void Assets::createTileTextures()
{
    auto width(5 * defaultTileSize), height(4 * defaultTileSize);

    m_TileRender = std::make_unique<sf::RenderTexture>();
    m_TileRender->create(width, height);
    m_TileRender->clear(sf::Color::Transparent);

    sf::RenderStates states;
    states.blendMode = sf::BlendNone;

    // Generate tile texture based on tilesize (for values 2 to 524288)
    NinePatch np{txRoundedRectSmall,{static_cast<float>(defaultTileSize), static_cast<float>(defaultTileSize)}};
    sf::Text text;
    text.setFont(fntCode);

    auto x(0.f), y(0.f);
    for (auto i(2), j(1); i <= 524288; i *= 2 , j++)
    {
        np.setPosition(x, y);
        np.setColor(colTiles[j - 1]);

        text.setFillColor(colTilesFont[j - 1]);
        text.setCharacterSize(45);
        text.setString(std::to_string(i));

        // Decrease font size based on the number of digits (TODO: rework font size calculation)
        auto fontSize(45);
        auto numDigits(static_cast<int>(std::floor(std::log10(i)) + 1));
        if (numDigits == 3)
        {
            fontSize -= 2;
        }
        else if (numDigits == 4)
        {
            fontSize -= 10;
        }
        else if (numDigits == 5)
        {
            fontSize -= 18;
        }
        else if (numDigits == 6)
        {
            fontSize -= 22;
        }
        else if (numDigits > 6) fontSize -= 4 * numDigits;

        text.setCharacterSize(fontSize);

        auto bounds(text.getLocalBounds());
        text.setOrigin(static_cast<float>(static_cast<int>(bounds.left + bounds.width / 2.f)), 
                       static_cast<float>(static_cast<int>(bounds.top + bounds.height / 2.f)));
        text.setPosition(x + defaultTileSize / 2.f, y + defaultTileSize / 2.f);

        m_TileRender->draw(np, states);
        m_TileRender->draw(text);

        if (j % 5 == 0)
        {
            // next row in tileset
            x = 0.f;
            y += defaultTileSize;
        }
        else
            x += defaultTileSize;
    }

    m_TileRender->display();
    txTile = &m_TileRender->getTexture();
}
