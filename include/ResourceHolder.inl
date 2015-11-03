template <typename Resource, typename Identifier>
template <typename... TArgs>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, TArgs&&... args)
{
    ResPtr resource{ new Resource };
    if (!resource->loadFromFile(filename, std::forward<TArgs>(args)...))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename... TArgs>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const void* data, std::size_t size, TArgs&&... args)
{
    ResPtr resource{ new Resource };
    if (!resource->loadFromMemory(data, size, std::forward<TArgs>(args)...))
        throw std::runtime_error("ResourceHolder::load - Failed to load resource from memory");

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found{ m_ResourceMap.find(id) };
    assert(found != m_ResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found{ m_ResourceMap.find(id) };
    assert(found != m_ResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, ResPtr resource)
{
    auto inserted{ m_ResourceMap.insert(std::make_pair(id, std::move(resource))) };
    assert(inserted.second);
}