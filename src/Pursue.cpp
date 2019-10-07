#include "Pursue.h"

Pursue::Pursue()
{
}

Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Agent *agent, float dtime)
{
	float T = (agent->getPosition() - agent->getTarget()).Length() / agent->getVelocity().Length();
	Vector2D predictedTarget = agent->getTarget() + agent->getMaxVelocity() * T;
	Vector2D desiredVelocity = predictedTarget - agent->getPosition();
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


