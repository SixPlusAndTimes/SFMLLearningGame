#ifndef SCENENODE_H
#define SCENENODE_H
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Category.hpp>
#include <CommandQueue.hpp>
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
    public:
                SceneNode(Category::Type catagory = Category::None);
        void    attachChild(Ptr child);
        Ptr     detachChild(const SceneNode& node);
        void    update(sf::Time dt, CommandQueue& commandQueue);
        sf::Vector2f    getWorldPosition() const;        
        sf::Transform   getWorldTransform() const;
        void            onCommand(const Command& command, sf::Time dt); 
        virtual unsigned int	getCategory() const;
    private:
        // must override the pure virtual func of the drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        // provide a new virtual func that can only draw current node not its children node
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void updateCurrent(sf::Time dt, CommandQueue& commandQueue);
        void         updateChildren(sf::Time dt, CommandQueue& commandQueue);

    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent; // weak pointer?
        Category::Type		mDefaultCategory;
};

float distance(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENENODE_H