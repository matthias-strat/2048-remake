#pragma once

// Pretty basic and simple configuration class, yet it fits my needs!
class Configuration
{
public:
    Configuration(const std::string& filename);

    bool load();
    bool save();

    unsigned int getVideoWidth() const { return m_VideoWidth; }
    unsigned int getVideoHeight() const { return m_VideoHeight; }
    bool getVSync() const { return m_VSync; }
    unsigned int getAntialiasing() const { return m_Antialiasing; }
    bool getShowFps() const { return m_ShowFps; }

    void setVideoWidth(unsigned int width) { m_WasUpdated = width != m_VideoWidth; m_VideoWidth = width; }
    void setVideoHeight(unsigned int height) { m_WasUpdated = height != m_VideoHeight; m_VideoHeight = height; }
    void setVSync(bool vsync) { m_WasUpdated = vsync != m_VSync; m_VSync = vsync; }
    void setAntialiasing(unsigned int level) { m_WasUpdated = level != m_Antialiasing; m_Antialiasing = level; }
    void setShowFps(bool show) { m_WasUpdated = show != m_ShowFps; m_ShowFps = show; }

private:
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    void setDefaultValues(bool updated = true);

    static const unsigned int DefaultVideoWidth;
    static const unsigned int DefaultVideoHeight;
    static const bool DefaultVSync;
    static const unsigned int DefaultAntialiasing;
    static const bool DefaultShowFps;

    std::string m_Filename;
    unsigned int m_VideoWidth, m_VideoHeight;
    bool m_VSync;
    unsigned int m_Antialiasing;
    bool m_ShowFps;

    bool m_WasUpdated;
};