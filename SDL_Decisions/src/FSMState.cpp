#include "FSMState.h"

//CHASE
void FSMChase::Enter(Agent* agent) {
	std::cout << "Entered Chase State" << std::endl;
}
FSMState* FSMChase::Update(Agent* agent, float dt) {
	if ((agent->getEnemy()->getPosition() - agent->getPosition()).Normalize < 30) {
		if (!agent->getEnemy()->hasGun()) {
			return NULL;
		}
		else {
			return FSMFlee;
		}
	}
	else {
		return FSMWander;
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
	if ((agent->getEnemy()->getPosition() - agent->getPosition()).Normalize < 30) {
		if (!agent->getEnemy()->hasGun()) {
			return FSMChase;
		}
		else {
			return FSMFlee;
		}
	}
	else {
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
	if ((agent->getEnemy()->getPosition() - agent->getPosition()).Normalize < 30) {
		if (!agent->getEnemy()->hasGun()) {
			return FSMChase;
		}
		else {
			return NULL;
		}
	}
	else {
		return FSMWander;
	}
}
void FSMFlee::Exit(Agent* agent) {

}