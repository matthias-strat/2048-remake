#pragma once

// Simple configuration class.
class Config
{
public:

    inline unsigned int getWindowWidth() const noexcept;
    inline unsigned int getWindowHeight() const noexcept;
    inline unsigned int getFullscreenWidth() const noexcept;
    inline unsigned int getFullscreenHeight() const noexcept;
    inline bool getFullscreen() const noexcept;

private:
    unsigned int m_WindowWidth, m_WindowHeight;
    unsigned int m_FullscreenWidth, m_FullscreenHeight;
    bool m_Fullscreen;
};