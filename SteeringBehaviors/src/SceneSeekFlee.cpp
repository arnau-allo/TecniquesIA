#include "SceneSeekFlee.h"
#include "Seek.h"
#include "Flee.h"

using namespace std;

SceneSeekFlee::SceneSeekFlee()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Seek);
	agent->setTarget(Vector2D(100, 100));
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
	agent = new Agent();
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(600,50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent); 
	target = Vector2D(100, 100);
}

SceneSeekFlee::~SceneSeekFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneSeekFlee::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
		}
		break;
	default:
		break;
	}
	target = agents[1]->getPosition();
	agents[0]->setTarget(target);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}
	
}

void SceneSeekFlee::draw()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneSeekFlee::getTitle()
{
	return "SDL Steering Behaviors :: Seek and Flee Demo";
}