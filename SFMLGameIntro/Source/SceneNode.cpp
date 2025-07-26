#include <SceneNode.hpp>
#include <algorithm>
#include <cassert>
#include <iostream>
#include "utils.hpp"

SceneNode::SceneNode(Category::Type catagory) 
: mChildren()
, mParent(nullptr)
, mDefaultCategory(catagory)
{

}

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found =  std::find_if(mChildren.begin(), mChildren.end(),
                    [&node](const Ptr& p)->bool {
                        return p.get() == &node;
                    } );

    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // state.transform holds the infomation where to render the parent node
    // getTransform return the transform infomation relative to the parent node
    states.transform *= getTransform(); 
    drawCurrent(target, states);

    for (const Ptr& child : mChildren) {
        child->draw(target, states);
    }
	drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // std::cout << "SceneNode Draw\n";
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void SceneNode::update(sf::Time dt, CommandQueue& commandQueue) 
{
    updateCurrent(dt, commandQueue);
    updateChildren(dt, commandQueue);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commandQueue) 
{

}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commandQueue) 
{
    for (const Ptr& child : mChildren) {
        child->update(dt, commandQueue);
    }
}

unsigned int SceneNode::getCategory() const
{
	return mDefaultCategory;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if (command.category & getCategory()) 
    {
        command.action(*this, dt);
    }
    for (auto& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

    for (Ptr& child : sceneGraph.mChildren)
    {
        checkNodeCollision(*child, collisionPairs);
    }
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
    {
        std::cout << "collision happen! between " << this->getCategory() <<  " and " << node.getCategory() << std::endl;
		collisionPairs.insert(std::minmax(this, &node));
    }

    for (Ptr& child : mChildren)
    {
		child->checkNodeCollision(node, collisionPairs);
    }
}

bool SceneNode::isDestroyed() const
{
    return false;
}

bool SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}
void SceneNode::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}
