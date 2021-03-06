#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include <deque>
#include "Grid.h"


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
	class PathFindingAlgorithm
	{
	public:
		PathFindingAlgorithm() {};
		virtual ~PathFindingAlgorithm() {};
		virtual void run(Agent *agent, float dtime) {};
	};
	class DecisionMakingAlgorithm
	{
	public:
		DecisionMakingAlgorithm() {};
		virtual ~DecisionMakingAlgorithm() {};
		virtual void update(Agent *agent, float dtime) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	// Pathfinding
	PathFindingAlgorithm* pathfinder;
	Path path;
	int currentTargetIndex;
	Grid *grid;

	// Decision Making
	DecisionMakingAlgorithm* brain;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	bool armed;
	Agent *enemy;

public:
	Agent();
	~Agent();

	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames = 1);

	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);

	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();

	bool hasGun();
	void setGun(bool gun);
	void setEnemy(Agent* agent);
	Agent* getEnemy();
	void setGrid(Grid *grid_);
	Grid* getGrid();
	int getHeuristic(Vector2D start, Vector2D end);
	Path getPathGreedy(Vector2D start, Vector2D end);
	Vector2D getRandomPosition();
	DecisionMakingAlgorithm* getBrain();
	void setBrain(DecisionMakingAlgorithm* brain_);
};
