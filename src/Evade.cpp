#include "Evade.h"

Evade::Evade()
{
}

Evade::~Evade()
{
}

void Evade::applySteeringForce(Agent *agent, float dtime)
{
	float T;
	if (agent->getVelocity() == 0)
	{
		T = (agent->getPosition() - agent->getAgentToPursue()->getPosition()).Length() / agent->getMaxVelocity();

	}
	else
	{
		T = (agent->getPosition() - agent->getAgentToPursue()->getPosition()).Length() / agent->getVelocity().Length();

	}
	Vector2D predictedTarget = agent->getAgentToPursue()->getPosition() + agent->getAgentToPursue()->getVelocity() * T;

	agent->setTarget(predictedTarget);

	Vector2D desiredVelocity = agent->getPosition() - agent->getTarget();
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


