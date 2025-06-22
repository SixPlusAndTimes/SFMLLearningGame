#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H
#include <string>
#include <map>
#include <memory>
#include <stdexcept> 
#include <cassert>

template<typename ResourceType, typename Identifier>
class ResourceHolder 
{
    public:
        ResourceHolder() = default;
        void load(Identifier id, const std::string& filename);

        template<typename Paramerter>
        void load(Identifier id, const std::string& filename, const Paramerter& secondParam);

        ResourceType& get(Identifier Id);
        const ResourceType& get(Identifier id) const;

    private:
        void insertResource(Identifier id, std::unique_ptr<ResourceType> resource);
    private:
        std::map<Identifier, std::unique_ptr<ResourceType>> mResourceMap; // why not vector or unorderedmap?
                                                         // cause both of them may suffer from reallocation of memory
};

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

#include <ResourceHolder.inl>
#endif // RESOURCEHOLDER_H