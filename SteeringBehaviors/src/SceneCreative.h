#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"


class SceneCreative :
	public Scene
{
public:
	SceneCreative();
	~SceneCreative();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Agent*> neighbors;

	Vector2D target;
};



