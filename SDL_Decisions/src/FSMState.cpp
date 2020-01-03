#include "FSMState.h"

void FSMChase::Enter(Agent* agent) {
	std::cout << "Entered Chase State" << std::endl;
}
void FSMChase::Update(Agent* agent, float dt) {

}
void FSMChase::Exit(Agent* agent) {

}

void FSMWander::Enter(Agent* agent) {
	std::cout << "Entered Wander State" << std::endl;
}
void FSMWander::Update(Agent* agent, float dt) {
	SceneDecisions* scene = agent->sensors->getScene();
}
void FSMWander::Exit(Agent* agent) {

}

void FSMFlee::Enter(Agent* agent) {
	std::cout << "Entered Flee State" << std::endl;
}
void FSMFlee::Update(Agent* agent, float dt) {

}
void FSMFlee::Exit(Agent* agent) {

}