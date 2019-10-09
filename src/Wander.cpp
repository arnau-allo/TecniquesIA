#include "Wander.h"

Wander::Wander()
{
	wanderRadius = 10;
	wanderOffset = 20;
	wanderMaxChange = 5;
	wanderAngle = 10;
}

Wander::~Wander()
{
}

void Wander::applySteeringForce(Agent *agent, float dtime)
{
	circleCenter = agent->getVelocity().Normalize()*wanderOffset;

	wanderAngle += (rand() % wanderMaxChange*2) - wanderMaxChange;

	Vector2D targetPos = (circleCenter.x + wanderRadius * cos(wanderAngle), circleCenter.y + wanderRadius * sin(wanderAngle));

	agent->setTarget(targetPos);
	
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




