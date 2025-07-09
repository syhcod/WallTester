#include <vector>
#include <math.h>
#include "dots.h"
#include "wallTest.h"

#pragma once


class Collider {
public:
	struct bDot {
		~bDot() {
			if (inter != nullptr) {
				delete inter;
			}
		}
		SDL_FPoint* inter = nullptr;
		bool coll = false;
	};
	bDot isCollision(Vec2 move, Wall* wall) {
		Vec2 vec;
		bDot bD;
		
		float yi=move.getStart().poll_y();
		float xi=move.getStart().poll_x();
		float xf=move.getFinish().poll_x();
		float yf=move.getFinish().poll_y();
		float a=wall->leftDot->poll_x();
		float b=wall->leftDot->poll_y();
		float c=wall->rightDot->poll_x();
		float d=wall->rightDot->poll_y();
		float det=((d-b)*(xf-xi)-(c-a)*(yf-yi));
		if (det == 0.0) {
			return bD;
		}
		float t=((yi-b)*(xf-xi)-(xi-a)*(yf-yi))/det;
		float s=((yi-b)*(c-a)-(xi-a)*(d-b))/det;

		if (0<=s && s<=1) {
			float x = xi + (xf - xi) * s;
			float y = yi + (yf - yi) * s;
			bD.inter = new SDL_FPoint;
			bD.inter->x = x;
			bD.inter->y = y;

			if (0<=t && t<=1) {
				bD.coll = true;
			}
		}
		return bD;
	}
	static bool isRight(dot c, Wall* wall){
		dot wall_L = *(wall->leftDot);
		dot wall_R = *(wall->rightDot);

		dot v1 = c - wall_L;
		dot v2 = wall_R - wall_L;

		float v3 = (v1.poll_x() * v2.poll_y()) - (v1.poll_y() * v2.poll_x());
		return v3 > 0;
	}

	dot projection(dot a, dot b, float size) {
		float times = (a.poll_y() * b.poll_y() + a.poll_x() * b.poll_x()) / size;
		dot in(a.poll_x() * times, a.poll_y() * times);
		return in;
	}

	void findWall(Vec2 move, Wall* root) {
		if (root == nullptr) {
			printf("Pushed back: %d\n", ++num);
			vecs.push_back(move);
			return;
		}
		printf("Finding wall: %dth iteration\n", ++d);

		bool vecSt_isR = isRight(move.getStart(), root);
		if (vecSt_isR != isRight(move.getFinish(), root)) {
			printf("Collision!\n");
			// TODO: Get intersectional point
			bDot bD = isCollision(move, root);
			SDL_FPoint* intermed = bD.inter;
			if (intermed != nullptr) {	// Means True collision has occured
				SDL_FPoint inter = *intermed;
				// delete intermed;
				Vec2 init(move.getStart(), inter);
				Vec2 fin(inter, move.getFinish());
				findWall(init, root->front);
				if (bD.coll) {
					//TODO: Create inner product of Fin on wall
					Vec2 nVec;
					dot wDiff = *(root->rightDot) - *(root->leftDot);
					dot vDiff = move.getFinish() - inter;
					float wsize = sqrt(wDiff.poll_x() * wDiff.poll_x() + wDiff.poll_y() * wDiff.poll_y());
					dot proj = projection(wDiff, vDiff, wsize);
					SDL_FPoint end = {inter.x + proj.poll_x(), inter.y + proj.poll_y()};

					nVec.setVec(inter, end);

					findWall(nVec, root->front);
				} else {
					printf("Can't believe null\n");
					findWall(fin, root->back);
				}
			} else {
				findWall(move, vecSt_isR ? root->back : root->front);
			}
		} else {
			findWall(move, root->back);
		}
	}

	Vec2* getVecs() {
		return vecs.data();
	}

	int getVecsNo() {
		return vecs.size();
	}
private:
	// Actual code will not include this!
	std::vector<Vec2> vecs;
	dot inter;
	int num = 0;
	int d = 0;
};