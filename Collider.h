#include <vector>
#include <math.h>
#include "dots.h"
#include "wallTest.h"

#pragma once


class Collider {
public:
	Vec2* collider(Wall* root, Vec2 move);
	static char isRight(dot c, Wall* wall);
	bool trueCollision(Wall* root, Vec2 move, SDL_FPoint* intersect);
	unsigned int getLength();
private:
	Wall* findWall(Wall* root, Vec2 move);
	Vec2 normalVec(Wall* wall, dot start, dot end);
	dot projection(dot a, dot b, float size);

	Wall* root;
	Wall* cWall;
	bool isRightWall;

	Vec2 cutVec;
	std::vector<Vec2> vecs;
	dot inter;
	int num = 0;
	int d = 0;
};