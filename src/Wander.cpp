#include "Wander.h"

Wander::Wander()
{
	
}

Wander::~Wander()
{
}

void Wander::applySteeringForce(Agent *agent, float dtime)
{
	
	
	//agent->setWanderAngle(agent->getWanderAngle() + (rand() % agent->getWanderMaxChange() * 2) - agent->getWanderMaxChange());

	/*
	agent->setWanderAngle(agent->getWanderAngle() + RandomBinomial()* agent->getWanderMaxChange());

	agent->setCircleCenter(agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset());

	agent->setDisplacementWander(agent->getDisplacementWander().Normalize() * agent->getWanderRadius());

	agent->setDisplacementWander((cos(agent->getWanderAngle()) * agent->getWanderRadius(), sin(agent->getWanderAngle()) * agent->getWanderRadius()));

	agent->setWanderAngle(agent->getWanderAngle() + rand() % (agent->getWanderMaxChange() * 2)  - agent->getWanderMaxChange());
	//std::cout << wanderCenter.x << " " << wanderCenter.y << std::endl;
	Vector2D wanderForce = agent->getCircleCenter() + agent->getDisplacementWander();
	*/

	agent->setCircleCenter(agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset());
	float angle = rand() % 2;
	angle *= 2 * M_PI;
	agent->setTarget((agent->getCircleCenter().x + agent->getWanderRadius() * cos(angle), agent->getCircleCenter().y + agent->getWanderRadius() * sin(angle)));
	
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

float Wander::RandomBinomial() {
	return (rand() / (1)) - (rand() / (1));
}



