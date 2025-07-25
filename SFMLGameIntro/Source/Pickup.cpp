#include "Pickup.hpp"
#include "ResourceHolder.hpp"
#include "DataTables.hpp"
#include "utils.hpp"
namespace
{
	const std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textures)
: Entity(1)
, mType(type)
, mSprite(textures.get(Table[type].texture))
{
	centerOrigin(mSprite);
}

void Pickup::apply(Aircraft& player) const
{
    Table[mType].action(player);
}

unsigned int Pickup::getCategory() const
{
	return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}