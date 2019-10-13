#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Wander.h"

class SceneWander :
	public Scene
{
public:
	SceneWander();
	~SceneWander();
	Wander _wander;
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};
