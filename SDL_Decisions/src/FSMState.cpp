#include "FSMState.h"

//CHASE
FSMChase::FSMChase(Agent* agent) {
	
}
void FSMChase::Enter(Agent* agent) {
	std::cout << "Entered Chase State" << std::endl;
}
FSMState* FSMChase::Update(Agent* agent, float dt) {
	//std::cout << "Update Chase State" << std::endl;

	Vector2D distanceVec = agent->getEnemy()->getPosition() - agent->getPosition();
	float distance = distanceVec.Length();

	if (distance < 200) {
		if (!agent->getEnemy()->hasGun()) {
			agent->clearPath();
			Vector2D destination = agent->getEnemy()->getPosition();
			if (agent->getGrid()->isValidCell(agent->getGrid()->pix2cell(destination))) {
				Path newPath = agent->getPathGreedy(agent->getGrid()->pix2cell(agent->getPosition()), agent->getGrid()->pix2cell(destination));
				for (int i = 0; i < newPath.points.size(); i++) {
					agent->addPathPoint(agent->getGrid()->cell2pix(newPath.points[i]));
				}
			}
			return nullptr;
		}
		else {
			return new FSMFlee(agent);
		}
	}
	else {
		return new FSMWander(agent);
	}
}
void FSMChase::Exit(Agent* agent) {
	std::cout << "Exit Chase State" << std::endl;

}

//WANDER
FSMWander::FSMWander(Agent* agent) {

}

void FSMWander::Enter(Agent* agent) {
	std::cout << "Entered Wander State" << std::endl;
	
}
FSMState* FSMWander::Update(Agent* agent, float dt) {
	//std::cout << "Update Wander State" << std::endl;

	draw_circle(TheApp::Instance()->getRenderer(), (int)agent->getPosition().x, (int)agent->getPosition().y, 200, 255, 255, 0, 255);

	Vector2D distanceVec = agent->getEnemy()->getPosition() - agent->getPosition();
	float distance = distanceVec.Length();

	if (distance < 200) {
		if (!agent->getEnemy()->hasGun()) {
			return new FSMChase(agent);
		}
		else {
			return new FSMFlee(agent);
		}
	}
	else {
		
		if (agent->getPathSize() == 0)
		{
			Vector2D destination = agent->getRandomPosition();
			Path newPath = agent->getPathGreedy(agent->getGrid()->pix2cell(agent->getPosition()), agent->getGrid()->pix2cell(destination));
			for (int i = 0; i < newPath.points.size(); i++) {
				agent->addPathPoint(agent->getGrid()->cell2pix(newPath.points[i]));
			}
		}
		return nullptr;
	}
}
void FSMWander::Exit(Agent* agent) {
	std::cout << "Exited Wander State" << std::endl;
}


//FLEE
FSMFlee::FSMFlee(Agent* agent) {

}
void FSMFlee::Enter(Agent* agent) {
	std::cout << "Entered Flee State" << std::endl;

}
FSMState* FSMFlee::Update(Agent* agent, float dt) {
	
	//std::cout << "Update Flee State" << std::endl;

	Vector2D distanceVec = agent->getEnemy()->getPosition() - agent->getPosition();
	float distance = distanceVec.Length();

	if (distance < 200) {
		if (!agent->getEnemy()->hasGun()) {
			return new FSMChase(agent);
		}
		else {
			agent->clearPath();
			Vector2D destination = agent->getEnemy()->getPosition();
			Path newPath = agent->getPathGreedy(agent->getGrid()->pix2cell(agent->getPosition()), agent->getGrid()->pix2cell(destination));
			for (int i = 0; i < newPath.points.size(); i++) {
				agent->addPathPoint(agent->getGrid()->cell2pix(newPath.points[i]));
			}
			return nullptr;
		}
	}
	else {
		return new FSMWander(agent);
	}
}
void FSMFlee::Exit(Agent* agent) {
	std::cout << "Exited Flee State" << std::endl;

}