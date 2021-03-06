#include "Agent.h"

using namespace std;

struct MyNode
{
	Vector2D position;
	MyNode *parent;
	float cost;
	float heuristic;
	float costSoFar;

	MyNode(Vector2D _pos, MyNode* _parent, float _cost, float _costSoFar) {
		position = _pos;
		parent = _parent;
		cost = _cost;
		costSoFar = _costSoFar;
	}
	MyNode(Vector2D _pos, MyNode* _parent, float _cost, float _costSoFar, float _heuristic) {
		position = _pos;
		parent = _parent;
		cost = _cost;
		heuristic = _heuristic;
		costSoFar = _costSoFar;
	}
	bool operator== (const MyNode &n) const {
		return (cost == n.cost);
	}
	bool operator > (const MyNode &n) const {
		return (cost > n.cost);
	}
	bool operator < (const MyNode &n) const {
		return (cost < n.cost);
	}
	bool operator >= (const MyNode &n) const {
		return (cost >= n.cost);
	}
	bool operator <= (const MyNode &n) const {
		return (cost <= n.cost);
	}

};

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
	             currentTargetIndex(-1),
				 mass(0.1f),
				 max_force(150),
				 max_velocity(200),
				 orientation(0),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
				 armed(false),
	             draw_sprite(false)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::update(float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;

	if (brain != nullptr) {
		brain->update(this, dtime);
	}
}


void Agent::addPathPoint(Vector2D point)
{
	if (path.points.size() > 0)
		if (path.points[path.points.size() - 1] == point)
			return;

	path.points.push_back(point);
}


int Agent::getCurrentTargetIndex()
{
	return currentTargetIndex;
}

int Agent::getPathSize()
{
	return path.points.size();
}

Vector2D Agent::getPathPoint(int idx)
{
	return path.points[idx];
}

void Agent::clearPath()
{
	setCurrentTargetIndex(-1);
	path.points.clear();
}

void Agent::setCurrentTargetIndex(int idx)
{
	currentTargetIndex = idx;
}

void Agent::draw()
{
	// Path
	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}

	
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

bool Agent::hasGun() {
	return armed;
}

void Agent::setGun(bool gun) {
	armed = gun;
}


void Agent::setEnemy(Agent* agent) {
	enemy = agent;
}

Agent* Agent::getEnemy() {
	return enemy;
}

void Agent::setGrid(Grid* grid_) {
	grid = grid_;
}

Grid* Agent::getGrid() {
	return grid;
}

int Agent::getHeuristic(Vector2D start, Vector2D end) {
	float distX = abs(start.x - end.x);
	float distY = abs(start.y - end.y);
	return distX > distY ? distX : distY;	
}

Path Agent::getPathGreedy(Vector2D start, Vector2D end) {
	std::deque<MyNode> visitedCells;
	MyNode n = MyNode(start, nullptr, 0, 0, getHeuristic(start, end));
	std::deque<MyNode> frontierGreedy;
	frontierGreedy.push_back(n);

	int it = 0;
	MyNode itNode = n;

	MyNode cheapestNode = frontierGreedy[0];

	while (!frontierGreedy.empty()) {

		int cheapI = 0;

		for (int i = 0; i < frontierGreedy.size() - 1; i++) {
			if (frontierGreedy[i].heuristic <= cheapestNode.heuristic) {
				cheapestNode = frontierGreedy[i];
				cheapI = i;
			}
		}
		itNode.position = frontierGreedy[cheapI].position;
		itNode.parent = frontierGreedy[cheapI].parent;
		itNode.heuristic = frontierGreedy[cheapI].heuristic;

		frontierGreedy.erase(frontierGreedy.begin() + cheapI);
		visitedCells.push_back(itNode);

		bool alreadyVisited = false;
		bool alreadyFrontier = false;
		Vector2D point2 = (0, 0);
		point2.x = itNode.position.x;
		point2.y = itNode.position.y - 1.0f;
		
		if (grid->isValidCell(point2)) {
			MyNode n2 = MyNode(point2, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point2));
			if (point2 == end) {
				visitedCells.push_back(n2);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point2) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point2) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					frontierGreedy.push_back(n2);
				}
			}
		}

		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point4 = (0, 0);
		point4.x = itNode.position.x - 1.0f;
		point4.y = itNode.position.y;
		if (grid->isValidCell(point4)) {
			MyNode n4 = MyNode(point4, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point4));
			if (point4 == end) {
				visitedCells.push_back(n4);
				break;
			}
			for (int i = 0; i < visitedCells.size() - 1; i++) {
				if (visitedCells[i].position == point4) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point4) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					frontierGreedy.push_back(n4);
				}
			}
		}

		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point6 = (0, 0);
		point6.x = itNode.position.x + 1.0f;
		point6.y = itNode.position.y;
		if (grid->isValidCell(point6)) {
			MyNode n6 = MyNode(point6, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point6));
			if (point6 == end) {
				visitedCells.push_back(n6);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point6) {
					alreadyVisited = true;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point2) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					frontierGreedy.push_back(n6);
				}
			}
		}

		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point8 = (0, 0);
		point8.x = itNode.position.x;
		point8.y = itNode.position.y + 1.0f;
		if (grid->isValidCell(point8)) {
			MyNode n8 = MyNode(point8, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point8));
			if (point8 == end) {
				visitedCells.push_back(n8);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point8) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point8) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					frontierGreedy.push_back(n8);
				}
			}
		}


		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point1 = (0, 0);
		point1.x = itNode.position.x - 1.0f;
		point1.y = itNode.position.y - 1.0f;
		if (grid->isValidCell(point1)) {
			MyNode n1 = MyNode(point1, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point1));
			if (point1 == end) {
				visitedCells.push_back(n1);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point1) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point1) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					//n8.costSoFar = n8.cost + n8.parent->costSoFar;
					frontierGreedy.push_back(n1);
				}
			}
		}

		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point3 = (0, 0);
		point3.x = itNode.position.x + 1.0f;
		point3.y = itNode.position.y - 1.0f;
		if (grid->isValidCell(point3)) {
			MyNode n3 = MyNode(point3, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point3));
			if (point3 == end) {
				visitedCells.push_back(n3);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point3) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point3) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					//n8.costSoFar = n8.cost + n8.parent->costSoFar;
					frontierGreedy.push_back(n3);
				}
			}
		}

		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point7 = (0, 0);
		point7.x = itNode.position.x - 1.0f;
		point7.y = itNode.position.y + 1.0f;
		if (grid->isValidCell(point7)) {
			MyNode n7 = MyNode(point7, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point7));
			if (point7 == end) {
				visitedCells.push_back(n7);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point7) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point7) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					//n8.costSoFar = n8.cost + n8.parent->costSoFar;
					frontierGreedy.push_back(n7);
				}
			}
		}

		alreadyVisited = false;
		alreadyFrontier = false;
		Vector2D point9 = (0, 0);
		point9.x = itNode.position.x + 1.0f;
		point9.y = itNode.position.y + 1.0f;
		if (grid->isValidCell(point9)) {
			MyNode n9 = MyNode(point9, &visitedCells[visitedCells.size() - 1], 0, 0, getHeuristic(end, point9));
			if (point9 == end) {
				visitedCells.push_back(n9);
				break;
			}
			for (int i = 0; i < visitedCells.size(); i++) {
				if (visitedCells[i].position == point9) {
					alreadyVisited = true;
					break;
				}
			}
			if (!alreadyVisited) {
				for (int i = 0; i < frontierGreedy.size(); i++) {
					if (frontierGreedy[i].position == point9) {

						alreadyFrontier = true;
						break;
					}
				}
				if (!alreadyFrontier) {
					//n8.costSoFar = n8.cost + n8.parent->costSoFar;
					frontierGreedy.push_back(n9);
				}
			}
		}


	}

	std::vector<Vector2D> points;
	bool isStart = false;
	bool pointFound = false;

	itNode = visitedCells[visitedCells.size() - 1];

	while (true) {
		points.push_back(itNode.position);
		if (itNode.parent != nullptr) {
			itNode = *itNode.parent;
		}
		else {
			break;
		}
	}

	Path myPath;
	for (int i = points.size() - 1; i >= 0; i--) {
		myPath.points.push_back(points[i]);
	}

	return myPath;
}

Vector2D Agent::getRandomPosition() {
	//srand(time(NULL));
	Vector2D randPosition = Vector2D(-1, -1);
	while ((!grid->isValidCell(randPosition)) ||( (Vector2D::Distance(randPosition, position) < 2))) {

		randPosition.x = (float)(rand() % grid->getNumCellX());
		randPosition.y = (float)(rand() % grid->getNumCellY());
		//randPosition = Vector2D((float)(rgand() % grid->getNumCellX()), (float)(rand() % grid->getNumCellY()));
	}
	return randPosition;

	//Vector2D randPosition = Vector2D(-1, -1);
	//while ((!grid->isValidCell(randPosition)) || ((Vector2D::Distance(randPosition, position) < 2))) {
	//	
	//	srand(time(NULL));
	//	
	//	float wanderAngle = rand()%360;
	//	

	//	float wanderRadius = 1;
	//	Vector2D positionCell = Vector2D(-1,-1);
	//	positionCell = Vector2D(grid->pix2cell(position));
	//	float componentX = positionCell.x + cos(wanderAngle) * wanderRadius;
	//	float componentY = positionCell.y + sin(wanderAngle) * wanderRadius;
	//	randPosition.x = componentX;
	//	randPosition.y = componentY;


	//	//randPosition = grid->pix2cell(randPosition);
	//}

	//return randPosition;
}


Agent::DecisionMakingAlgorithm* Agent::getBrain() {
	return brain;
}

void Agent::setBrain(Agent::DecisionMakingAlgorithm* brain_) {
	brain = brain_;
}