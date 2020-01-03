#include "SensorySystem.h"

SensorySystem::SensorySystem()
{

}

SensorySystem::~SensorySystem()
{

}

void SensorySystem::update(Agent *agent, float dtime) {

}

void SensorySystem::setWorld(SceneDecisions *world_) {
	world = world_;
}

SceneDecisions* SensorySystem::getScene() {
	return world;
}