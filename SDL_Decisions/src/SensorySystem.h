#pragma once
#include "SceneDecisions.h"
#include "Agent.h"

class SensorySystem
{
private:
	Scene *world;
public:
	SensorySystem();
	~SensorySystem();
	void update(Agent* agent, float dtime);
	void setWorld(SceneDecisions *world_);
	SceneDecisions* getScene();
};

