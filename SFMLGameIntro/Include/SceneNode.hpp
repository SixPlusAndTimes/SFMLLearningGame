#ifndef SCENENODE_H
#define SCENENODE_H
#include <memory>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include <Category.hpp>
#include <CommandQueue.hpp>
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
        typedef std::pair<SceneNode*, SceneNode*> Pair;
    public:
		explicit        SceneNode(Category::Type category = Category::None);
        void            attachChild(Ptr child);
        Ptr             detachChild(const SceneNode& node);
        void            update(sf::Time dt, CommandQueue& commandQueue);
        sf::Vector2f    getWorldPosition() const;        
        sf::Transform   getWorldTransform() const;
        void            onCommand(const Command& command, sf::Time dt); 
        virtual unsigned int	getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

        void            checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);

        void            removeWrecks();
        virtual bool    isDestroyed() const;
        virtual bool    isMarkedForRemoval() const;
    private:
        // must override the pure virtual func of the drawable
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
        // provide a new virtual func that can only draw current node not its children node
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void    drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const;
        virtual void    updateCurrent(sf::Time dt, CommandQueue& commandQueue);
        void            updateChildren(sf::Time dt, CommandQueue& commandQueue);

        void            checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);

    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent; // weak pointer?
        Category::Type		mDefaultCategory;
};

bool  collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENENODE_H