#include <time.h>
#include "Wander.h"

Wander::Wander()
{
	
}

Wander::~Wander()
{
}

void Wander::applySteeringForce(Agent *agent, float dtime)
{
	srand(time(NULL));
	
	//agent->setWanderAngle(agent->getWanderAngle() + (rand() % agent->getWanderMaxChange() * 2) - agent->getWanderMaxChange());
	//float randNum = RandomFloat(-agent->getWanderMaxChange(), agent->getWanderMaxChange());
	float binomial = (float)(rand() % 2 - rand() % 2);
	//float randomAngle = (rand() % (int)agent->getWanderMaxChange() * 2 - agent->getWanderMaxChange());
	
	//float randNum = (float)((rand() % 10000 * binomial*agent->getWanderMaxChange()) / 10000);


	float randNum = (rand() % 1000)*agent->getWanderMaxChange();
	randNum /= 1000;
	std::cout << randNum << std::endl;
	agent->setWanderAngle(agent->getWanderAngle() + binomial* agent->getWanderMaxChange());

	if (agent->getWanderAngle() > maxAngle || agent->getWanderAngle() < -maxAngle) {
		agent->setWanderAngle(agent->getWanderAngle() + -binomial * agent->getWanderMaxChange());
	}
	

	agent->setCircleCenter(agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset());

	Vector2D tempVec = Vector2D(agent->getCircleCenter().x + cos(agent->getWanderAngle()) * agent->getWanderRadius(), agent->getCircleCenter().y + sin(agent->getWanderAngle()) * agent->getWanderRadius());

	//agent->setDisplacementWander();

	
	
	agent->setTarget(tempVec);
	//std::cout << randNum << std::endl;
	//std::cout << tempVec.x << " " << tempVec.y << std::endl;

/*
	agent->setCircleCenter(agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset());
	float angle = rand() % 2;
	angle *= 2 * M_PI;
	agent->setTarget((agent->getCircleCenter().x + agent->getWanderRadius() * cos(angle), agent->getCircleCenter().y + agent->getWanderRadius() * sin(angle)));
*/
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
	return (rand() % 2 - rand() % 2);
}

float Wander::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}



