#include <SceneNode.hpp>
#include <algorithm>
#include <cassert>
#include <iostream>

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
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // std::cout << "SceneNode Draw\n";
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
    return Category::SceneAirLayer;
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
