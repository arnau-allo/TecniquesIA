#include "FSMState.h"

//CHASE
FSMChase::FSMChase(Agent* agent) {
	
}
void FSMChase::Enter(Agent* agent) {
	std::cout << "Entered Chase State" << std::endl;
}
FSMState* FSMChase::Update(Agent* agent, float dt) {

	Vector2D distanceVec = agent->getEnemy()->getPosition() - agent->getPosition();
	float distance = distanceVec.Length();

	if (distance < 30) {
		if (!agent->getEnemy()->hasGun()) {
			return NULL;
		}
		else {
			return new FSMFlee(agent);
		}
	}
	else {
		return new FSMWander(agent);
	}
}
void FSMChase::Exit(Agent* agent) {

}

//WANDER
FSMWander::FSMWander(Agent* agent) {

}

void FSMWander::Enter(Agent* agent) {
	std::cout << "Entered Wander State" << std::endl;
	
}
FSMState* FSMWander::Update(Agent* agent, float dt) {

	Vector2D distanceVec = agent->getEnemy()->getPosition() - agent->getPosition();
	float distance = distanceVec.Length();

	if (distance < 30) {
		if (!agent->getEnemy()->hasGun()) {
			return new FSMChase(agent);
		}
		else {
			return new FSMFlee(agent);
		}
	}
	else {
		
		if (agent->getPathSize() == 0)
		{
			Vector2D destination = agent->getRandomPosition();
			Path newPath = agent->getPathGreedy(agent->getPosition(), destination);
			for (int i = 0; i < newPath.points.size(); i++) {
				agent->addPathPoint(agent->getGrid()->cell2pix(newPath.points[i]));
			}
		}
		return NULL;
	}
}
void FSMWander::Exit(Agent* agent) {

}


//FLEE
FSMFlee::FSMFlee(Agent* agent) {

}
void FSMFlee::Enter(Agent* agent) {
	std::cout << "Entered Flee State" << std::endl;
	//CURRENT BEHAVIOUR = NEW BEHAVIOUR
}
FSMState* FSMFlee::Update(Agent* agent, float dt) {
	//CURRENT_BEHAVIOUR UPDATE

	Vector2D distanceVec = agent->getEnemy()->getPosition() - agent->getPosition();
	float distance = distanceVec.Length();

	if (distance < 30) {
		if (!agent->getEnemy()->hasGun()) {
			return new FSMChase(agent);
		}
		else {
			return NULL;
		}
	}
	else {
		return new FSMWander(agent);
	}
}
void FSMFlee::Exit(Agent* agent) {

}