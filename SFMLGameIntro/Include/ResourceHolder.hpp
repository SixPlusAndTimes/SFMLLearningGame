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


#include <ResourceHolder.inl>
#endif // RESOURCEHOLDER_H