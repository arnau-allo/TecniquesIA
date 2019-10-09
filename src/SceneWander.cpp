#include "SceneWander.h"
#include "Agent.h"
#include "Evade.h"
#include "Seek.h"
#include "Wander.h"



SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Wander);
	agent->setPosition(Vector2D(600, 50));
	agent->setTarget(Vector2D(900, 650));
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
	switch (event->type) {
	case SDL_MOUSEMOTION:
		/*case SDL_MOUSEBUTTONDOWN:
			if (event->button.button == SDL_BUTTON_LEFT)
			{
				target = Vector2D((float)(event->button.x), (float)(event->button.y));
				agents[0]->setTarget(target);
			}
			break;
		default:
			break;
		}*/

		//agents[0]->setTarget(target);

		for (int i = 0; i < (int)agents.size(); i++)
		{
			agents[i]->update(dtime, event);
		}
	}
}

void SceneWander::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 55, 0, 255, 0);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Pursue Demo";
}
