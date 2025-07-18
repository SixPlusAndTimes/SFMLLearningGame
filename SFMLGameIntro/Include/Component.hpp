#ifndef COMPONENT_H
#define COMPONENT_H
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
namespace sf
{
    class Event;
} // namespace sf

namespace GUI
{
class Component : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::shared_ptr<Component> Ptr;
    public:
							Component();
        virtual				~Component();

        virtual bool		isSelectable() const = 0;
		bool				isSelected() const;
        virtual void		select();
        virtual void		deselect();

        virtual bool		isActive() const;
        virtual void		activate();
        virtual void		deactivate();

        virtual void		handleEvent(const sf::Event& event) = 0;
    private:
        bool				mIsSelected;
        bool				mIsActive;
};
}

#endif // COMPONENT_H