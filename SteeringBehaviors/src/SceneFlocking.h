#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"


class SceneFlocking :
	public Scene
{
public:
	SceneFlocking();
	~SceneFlocking();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Agent*> neighbors;

	Vector2D target;
};



