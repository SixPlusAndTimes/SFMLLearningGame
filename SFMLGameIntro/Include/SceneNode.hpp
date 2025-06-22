#ifndef SCENENODE_H
#define SCENENODE_H
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
    public:
                SceneNode();
        void    attachChild(Ptr child);
        Ptr     detachChild(const SceneNode& node);
        void    update(sf::Time dt);
        sf::Vector2f    getWorldPosition() const;        
        sf::Transform   getWorldTransform() const;
    private:
        // must override the pure virtual func of the drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        // provide a new virtual func that can only draw current node not its children node
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void updateCurrent(sf::Time dt);
        void         updateChildren(sf::Time dt);
    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent; // weak pointer?
};


#endif // SCENENODE_H