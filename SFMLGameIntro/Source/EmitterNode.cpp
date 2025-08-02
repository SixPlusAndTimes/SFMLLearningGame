#include "EmitterNode.hpp"

EmitterNode::EmitterNode(Particle::Type type)
: SceneNode()
, mAccumulatedTime(sf::Time::Zero)
, mType(type)
, mParticleSystem(nullptr) { }

void EmitterNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // if emitter is corresponding to a particle system, just emit the particle
    // otherwise, we should find the particle system first
    if (mParticleSystem)
    {
        emitParticles(dt);
    }
    else 
    {
        Command command;
        command.category = Category::ParticleSystem;
        command.action = derivedAction<ParticleNode>([this](ParticleNode& node, sf::Time dt){;
            if (node.getParticleType() == mType)
            {
                this->mParticleSystem = &node;
            }
        });
        commands.push(std::move(command));
    }
}

void EmitterNode::emitParticles(sf::Time dt)
{
	const float emissionRate = 30.f;
	const sf::Time interval = sf::seconds(1.f) / emissionRate;

	mAccumulatedTime += dt;

	while (mAccumulatedTime > interval)
	{
		mAccumulatedTime -= interval;
		mParticleSystem->addParticle(getWorldPosition());
	}
}
