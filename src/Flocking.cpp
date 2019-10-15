#include "Flocking.h"
#include <vector>

Flocking::Flocking()
{
}

Flocking::~Flocking()
{
}

void Flocking::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D separationVector = (0, 0);
	int neighborCount = 0;
	std::vector<Agent*> neighbors = agent->getNeighbors();
	Vector2D separationDirection;

	for (int i = 0; i < neighbors.size(); i++) {
		if ((agent->getPosition() - neighbors[i]->getPosition()).Length() < neighborRadius) {
			separationVector += (agent->getPosition() - neighbors[i]->getPosition());
			neighborCount++;
		}
	}

	if (neighborCount > 0) {
		separationVector /= neighborCount;
		separationDirection = separationVector.Normalize();
	}
	
	

	Vector2D cohesionDirection;
	Vector2D averagePosition = (0, 0);
	neighborCount = 0;

	for (int i = 0; i < neighbors.size(); i++) {
		if ((agent->getPosition() - neighbors[i]->getPosition()).Length() < neighborRadius) {
			averagePosition += neighbors[i]->getPosition();
			neighborCount++;
		}
	}

	if (neighborCount > 0) {
		averagePosition /= neighborCount;
		averagePosition -= agent->getPosition();
		cohesionDirection = averagePosition.Normalize();
	}
	



	Vector2D alignmentDirection;
	Vector2D averageVelocity = (0,0);
	neighborCount = 0;

	for (int i = 0; i < neighbors.size(); i++) {
		if ((agent->getPosition() - neighbors[i]->getPosition()).Length() < neighborRadius) {
			averageVelocity += (neighbors[i]->getVelocity());
			neighborCount++;
		}
	}

	if (neighborCount > 0) {
		averageVelocity /= neighborCount;
		alignmentDirection = averageVelocity.Normalize();
	}

	Vector2D flockingForce = separationDirection * K_SEPARATION_FORCE + cohesionDirection * K_COHESION_FORCE + alignmentDirection * K_ALIGNMENT_FORCE;

	flockingForce = flockingForce.Normalize() * agent->getMaxVelocity();

	agent->setTarget(agent->getPosition() + flockingForce);

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


