#pragma once

#include "Common.hpp"

// Simple nine patch class with a fixed patch grid. (patchWidth = textureSize/3, patchHeight = textureSize/3)
class NinePatch : public sf::Drawable, public sf::Transformable
{
public:
    NinePatch() = default;
    NinePatch(const sf::Texture& texture, const Vec2f& size) noexcept;

    NinePatch(const NinePatch&) = delete;
    NinePatch& operator=(const NinePatch&) = delete;

    void setTexture(const sf::Texture& texture);
    void setSize(const Vec2f& size);

    const Vec2f& getSize() const noexcept;
    const Vec2f& getMinSize() const noexcept;
    const Vec2f& getPatchSize() const noexcept;

    void setColor(const sf::Color& color) noexcept;
    const sf::Color& getColor() const noexcept;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateSizes() noexcept;
    void ensureMinSize() noexcept;
    void updateVertices() noexcept;
    void updateVerticesPos() noexcept;
    void updateVerticesTexCoord() noexcept;

private:
    static constexpr int vertexCount{36}; // 9 * 4

    std::array<sf::Vertex, vertexCount> m_Vertices;
    const sf::Texture* m_Texture{nullptr};
    bool m_UpdateTexCoords{true}, m_UpdatePos{true};
    Vec2f m_Size, m_MinSize, m_PatchSize;
};
