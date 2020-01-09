#include "FSMState.h"

//CHASE
void FSMChase::Enter(Agent* agent) {
	std::cout << "Entered Chase State" << std::endl;
}
FSMState* FSMChase::Update(Agent* agent, float dt) {
	if ((agent->getEnemy()->getPosition() - agent->getPosition()).Length < 30) {
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
void FSMWander::Enter(Agent* agent) {
	std::cout << "Entered Wander State" << std::endl;
	
}
FSMState* FSMWander::Update(Agent* agent, float dt) {
	SceneDecisions* scene = agent->sensors->getScene();
	if ((agent->getEnemy()->getPosition() - agent->getPosition()).Length < 30) {
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
				agent->addPathPoint(agent->getGrid->cell2pix(newPath.points[i]));
			}
		}
		return NULL;
	}
}
void FSMWander::Exit(Agent* agent) {

}


//FLEE
void FSMFlee::Enter(Agent* agent) {
	std::cout << "Entered Flee State" << std::endl;
	//CURRENT BEHAVIOUR = NEW BEHAVIOUR
}
FSMState* FSMFlee::Update(Agent* agent, float dt) {
	//CURRENT_BEHAVIOUR UPDATE
	if ((agent->getEnemy()->getPosition() - agent->getPosition()).Length < 30) {
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