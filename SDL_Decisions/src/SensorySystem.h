#pragma once
#include "SceneDecisions.h"

class SensorySystem
{
private:
	SceneDecisions* world;
public:
	SensorySystem();
	~SensorySystem();
	void update(Agent* agent, float dtime);
	void setWorld(SceneDecisions* world_);
	SceneDecisions* getScene();
};

