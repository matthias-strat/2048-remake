#pragma once

//Represents a template class for a simple resource manager which stores items and allows to re-use them.
template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    template <typename... TArgs>
    void load(Identifier id, const std::string& filename, TArgs&&... args);

    template <typename... TArgs>
    void load(Identifier id, const void* data, std::size_t size, TArgs&&... args);

    Resource& get(Identifier id);
    const Resource& get(Identifier) const;

private:
    using ResPtr = std::unique_ptr<Resource>;

    void insertResource(Identifier id, ResPtr resource);

    std::map<Identifier, ResPtr> m_ResourceMap;
};
#include "ResourceHolder.inl"