#include "SceneEvade.h"
#include "Agent.h"
#include "Evade.h"
#include "Seek.h"



SceneEvade::SceneEvade()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(600, 50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(100, 100);

	agent = new Agent();
	agent->setBehavior(new Evade);
	agent->setTarget(Vector2D(100, 100));
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agent->setAgentToPursue(agents[0]);
	agents.push_back(agent);

}

//Agents[0] soldier, Agents[1] zombie

SceneEvade::~SceneEvade()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneEvade::update(float dtime, SDL_Event *event) {
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}

	agents[0]->setTarget(target);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}
}

void SceneEvade::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 55, 0, 255, 0);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneEvade::getTitle()
{
	return "SDL Steering Behaviors :: Evade Demo";
}
