#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics/Text.hpp>

#include "Component.hpp"
#include "ResourceIdentifier.hpp"
#include "ResourceHolder.hpp"

namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;
            

	public:
							Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
		void				setText(const std::string& text);

        virtual void		handleEvent(const sf::Event& event);


    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			mText;
};

}

#endif // LABEL_H