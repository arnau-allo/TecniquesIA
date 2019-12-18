#include <time.h>
#include "SceneFlocking.h"
#include "Agent.h"
#include "Pursue.h"
#include "Seek.h"
#include "Flocking.h"



SceneFlocking::SceneFlocking()
{
	srand(time(NULL));
	Agent *agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(rand() % 600, rand() % 600));
	agent->setVelocity(Vector2D(rand() % 10, rand() % 10));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	neighbors.push_back(agent);
	
	agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(rand() % 600, rand() % 600));
	agent->setVelocity(Vector2D(rand() % 10, rand() % 10));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	neighbors.push_back(agent);


	agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(rand() % 600, rand() % 600));
	agent->setVelocity(Vector2D(rand() % 10, rand() % 10));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	neighbors.push_back(agent);


	agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(rand() % 600, rand() % 600));
	agent->setVelocity(Vector2D(rand() % 10, rand() % 10));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	neighbors.push_back(agent);

 
	agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(rand() % 600, rand() % 600));
	agent->setVelocity(Vector2D(rand() % 10, rand() % 10));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	neighbors.push_back(agent);


	agent = new Agent;
	agent->setBehavior(new Flocking);
	agent->setPosition(Vector2D(rand() % 600, rand() % 600));
	agent->setVelocity(Vector2D(rand() % 10, rand() % 10));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	neighbors.push_back(agent);

	for (int i = 0; i < agents.size(); i++) {
		agents[i]->setNeighbors(neighbors);
	}
}

//Agents[0] soldier, Agents[1] zombie

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event) {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}
	
}

void SceneFlocking::draw()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
		draw_circle(TheApp::Instance()->getRenderer(), (int)agents[i]->getPosition().x, (int)agents[i]->getPosition().y, 200, 55, 0, 255, 0);
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking Demo";
}

