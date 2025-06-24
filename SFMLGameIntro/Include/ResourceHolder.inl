
template<typename ResourceType, typename Identifier>
void ResourceHolder<ResourceType, Identifier>::load(Identifier id, const std::string& filename) {
    std::unique_ptr<ResourceType> resource = std::make_unique<ResourceType>();
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }

    insertResource(id, std::move(resource));    
}

template<typename ResourceType, typename Identifier>
template<typename Parameter>
void ResourceHolder<ResourceType, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam) {
    std::unique_ptr<ResourceType> resource = std::make_unique<ResourceType>();
    if (!resource->loadFromFile(filename, secondParam)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }

    insertResource(id, std::move(resource));    
}


template<typename ResourceType, typename Identifier>
ResourceType& ResourceHolder<ResourceType, Identifier>::get(Identifier Id) {
    auto found = mResourceMap.find(Id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template<typename ResourceType, typename Identifier>
const ResourceType& ResourceHolder<ResourceType, Identifier>::get(Identifier Id) const {
    auto found = mResourceMap.find(Id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template<typename ResourceType, typename Identifier>
void ResourceHolder<ResourceType, Identifier>::insertResource(Identifier id, std::unique_ptr<ResourceType> resource) {
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}