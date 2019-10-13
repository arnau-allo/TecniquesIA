#include "Agent.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
			position(Vector2D(100, 100)),
			target(Vector2D(1000, 100)),
			velocity(Vector2D(0, 0)),
			speed(0.5),
			max_force(1),
			max_velocity(200),
			orientation(0),
			sprite_num_frames(0),
			sprite_w(0),
			sprite_h(0),
			slowingRadius(100),
			draw_sprite(false),

	//WANDER
			wanderRadius(50),
			wanderOffset(100),
			wanderMaxChange(5),
			wanderAngle(10),
			displacementWander(Vector2D(0, -1))
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
	return speed;
}

float Agent::getSlowingRadius()
{
	return slowingRadius;
}

Agent* Agent::getAgentToPursue() 
{
	return agentToPursue;
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
void Agent::setAgentToPursue(Agent* agent) 
{
	agentToPursue = agent;
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
}

void Agent::draw()
{
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

//WANDER
float  Agent::getWanderAngle() {
	return wanderAngle;
};
float  Agent::getWanderRadius() {
	return wanderRadius;
};
float  Agent::getWanderOffset() {
	return wanderOffset;
};
int  Agent::getWanderMaxChange() {
	return wanderMaxChange;
};
Vector2D  Agent::getCircleCenter() {
	return circleCenter;
};
Vector2D Agent::getDisplacementWander() {
	return displacementWander;
}
void  Agent::setWanderAngle(float angle) {
	wanderAngle = angle;
};
void  Agent::setWanderRadius(float radius) {
	wanderRadius = radius;
};
void  Agent::setWanderOffset(float offset) {
	wanderOffset = offset;
};
void  Agent::setWanderMaxChange(int MaxChange) {
	wanderMaxChange = MaxChange;
};
void  Agent::setCircleCenter(Vector2D pos) {
	circleCenter = pos;
};

void Agent::setDisplacementWander(Vector2D vec) {
	displacementWander = vec;
}

//FLOCKING
std::vector<Agent*> Agent::getNeighbors() {
	return neighbors;
}

void Agent::setNeighbors(std::vector<Agent*> vector) {
	neighbors = vector;
}