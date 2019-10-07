#include "Seek.h"

Seek::Seek() 
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	

	/*Vector2D steering = agent->getTarget() - agent->getPosition();
	steering.Normalize();
	
	steering *= agent->getMaxVelocity();
	Vector2D steeringForce = (steering - agent->getVelocity());

	steeringForce = steeringForce.Normalize()*agent->getMaxForce();

	agent->setVelocity(steeringForce + agent->getVelocity().Normalize() * agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() *dtime);*/


	float factor;
	if ((agent->getTarget() - agent->getPosition()).Length() > agent->getSlowingRadius()) {
		factor = 1;
	}
	else {
		factor = (agent->getTarget() - agent->getPosition()).Length() / agent->getSlowingRadius();
	}

	Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
	//desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();

	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();

	steeringForce *= agent->getMaxForce();

	Vector2D acceleration = steeringForce / agent->getMass();
	agent->setVelocity(agent->getVelocity() + acceleration * dtime);
	agent->setVelocity(agent->getVelocity().Truncate(agent->getMaxVelocity()*factor));

	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);

	/*if ((agent->getTarget() - agent->getPosition()).Length() > agent->getSlowingRadius()) {
		Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
		//desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity();

		Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
		steeringForce /= agent->getMaxVelocity();

		steeringForce *= agent->getMaxForce();

		Vector2D acceleration = steeringForce / agent->getMass();
		agent->setVelocity(agent->getVelocity() + acceleration * dtime);
		agent->setVelocity(agent->getVelocity().Truncate(agent->getMaxVelocity()));

		agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
	}
	else {
		float factor = (agent->getTarget() - agent->getPosition()).Length() / agent->getSlowingRadius();
		Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
		//desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity();

		Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
		steeringForce /= agent->getMaxVelocity();

		steeringForce *= agent->getMaxForce();

		Vector2D acceleration = steeringForce / agent->getMass();
		agent->setVelocity(agent->getVelocity() + acceleration * dtime);
		agent->setVelocity(agent->getVelocity().Truncate(agent->getMaxVelocity()*factor));

		agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
	}*/
	

} // This is NOT the Seek Steering Behavior!!! We must take into account acceleration!


