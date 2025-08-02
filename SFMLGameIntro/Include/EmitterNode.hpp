#ifndef EMITTERNODE_H
#define EMITTERNODE_H
#include "SceneNode.hpp"
#include "ParticleNode.hpp"

class ParticleNode;

class EmitterNode : public SceneNode
{
	public:
		explicit				EmitterNode(Particle::Type type);


	private:
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		
		void					emitParticles(sf::Time dt);


	private:
		sf::Time				mAccumulatedTime; // used to control the speed of Emitter to emit the particle into particle system(i.e. particlenode)
		Particle::Type			mType;              // this is particle type not the type in the Category.hpp filec
		ParticleNode*			mParticleSystem;  
};

#endif // EMITTERNODE_H