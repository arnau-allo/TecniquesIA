#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <vector>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:

		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Agent* agentToPursue;

	float speed; //change to mass
	float orientation;
	float max_force;
	float max_velocity;
	float slowingRadius;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	//WANDER
	float wanderAngle;
	float wanderRadius;
	float wanderOffset;
	float wanderMaxChange;
	Vector2D circleCenter;
	Vector2D displacementWander;

	//FLOCKING
	std::vector<Agent*> neighbors;

	
public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxForce();
	float getMaxVelocity();
	float getMass();
	float getSlowingRadius();
	Agent* getAgentToPursue();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setAgentToPursue(Agent* agent);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);

	//WANDER
	float getWanderAngle();
	float getWanderRadius();
	float getWanderOffset();
	float getWanderMaxChange();
	Vector2D getCircleCenter();
	Vector2D getDisplacementWander();
	void setWanderAngle(float angle);
	void setWanderRadius(float radius);
	void setWanderOffset(float offset);
	void setWanderMaxChange(float MaxChange);
	void setCircleCenter(Vector2D pos);
	void setDisplacementWander(Vector2D vec);

	//FLOCKING
	std::vector<Agent*> getNeighbors();
	void setNeighbors(std::vector<Agent*> vector);
	
};
