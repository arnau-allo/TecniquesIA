#include "SceneWander.h"
#include "Agent.h"
#include "Evade.h"
#include "Seek.h"
#include "Wander.h"



SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Wander);
	agent->setPosition(Vector2D(300, 300));
	agent->setVelocity(Vector2D(10,0));
	//agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(100, 100);

}

//Agents[0] soldier, Agents[1] zombie

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event *event) {
	/* Keyboard & Mouse events */
	
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}
}

void SceneWander::draw()
{
	
	draw_circle(TheApp::Instance()->getRenderer(), (int)agents[0]->getCircleCenter().x, (int)agents[0]->getCircleCenter().y, (int)agents[0]->getWanderRadius(), 55, 0, 255, 0);
	draw_circle(TheApp::Instance()->getRenderer(), (int)agents[0]->getTarget().x, (int)agents[0]->getTarget().y, 5, 0, 255, 255, 0);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)agents[0]->getCircleCenter().x, (int)agents[0]->getCircleCenter().y, (int)agents[0]->getCircleCenter().x + agents[0]->getWanderRadius() * cos(agents[0]->getWanderAngle()), (int)agents[0]->getCircleCenter().x + agents[0]->getWanderRadius() * sin(agents[0]->getWanderAngle()));
	
	//draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 55, 255, 103, 255);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}
