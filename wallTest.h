#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Types.h"


typedef struct Wall {

	~Wall() {
		delete vec;
	}

	Wall* front = nullptr;
	Wall* back = nullptr;
	dot* leftDot = nullptr;
	dot* rightDot = nullptr;
	Vec2* vec = nullptr;

	bool isObject = false;

	Vec2* vec2() {
		vec = new Vec2();
		vec->leftDot = leftDot;
		vec->rightDot = rightDot;
		return vec;
	}

} Wall;

class Walls {
public:
	// full path file must be given for dotsFile and wallFile
	Walls(const char* dotsFile, const char* wallFile, const int wallNo) {
		readDotsFile(dotsFile);
		readWallFile(wallFile);
	}
	~Walls() {
		free(wallDots);
	}
	Wall* getRoot() {
		return root;
	}
private:
	Wall* root;
	dot** wallDots;
	int wallNo;
	bool spriteIsRead = false;

	std::vector<Wall*>ObjNodes;

	// How the file must be structured 
	// %d %d %d %d %d\n -> Ldot Rdot frontWall backWall wallHeight
	// %s %s\n       -> frontWallTexture backWallTexture
	// front/backWall is 0 if there is none
	// full filepath must be specified for wall textures.
	void readWallFile(const char* wallFile) {
		// printf("Reading wall file\n");
		FILE* fptr = fopen(wallFile, "r");
		Wall** bufferWalls = (Wall**)malloc(wallNo * sizeof(Wall*));
		int leftDot, rightDot, frontWall, backWall;
		float wallHeight;
		char frontFile[64];
		char backFile[64];
		for (int i = 0; i < wallNo; i++) {
			bufferWalls[i] = new Wall();
		}
		for (int i = 0; i < wallNo; i++) {
			// printf("Reading wall %d\n", i);
			fscanf(fptr, "%d %d %d %d %f\n", &leftDot, &rightDot, &frontWall, &backWall, &wallHeight);
			bufferWalls[i]->leftDot = wallDots[leftDot];
			bufferWalls[i]->rightDot = wallDots[rightDot];

			if (frontWall != 0) {
				// printf("Front wall: %d\n", frontWall);
				bufferWalls[i]->front = bufferWalls[frontWall];
			}
			else {
				// printf("No front wall\n");
				bufferWalls[i]->front = nullptr;
			}
			if (backWall != 0) {
				// printf("Back wall: %d\n", backWall);
				bufferWalls[i]->back = bufferWalls[backWall];
			}
			else {
				// printf("No back wall\n");
				bufferWalls[i]->back = nullptr;
			}
		}
		root = *bufferWalls;
		free(bufferWalls);
	}



	// How the file must be structured
	// %d\n     -> wallNo
	// %d %d\n  -> rad deg (This constinues on for 'wallNo' amount of times)
	void readDotsFile(const char* dotsFile) {
		FILE* fptr = fopen(dotsFile, "r");
		fscanf(fptr, "%d\n", &wallNo);
		wallDots = (dot**)malloc(wallNo * sizeof(dot*));
		for (int i = 0; i < wallNo; i++) {
			wallDots[i] = new dot();
		}
		for (int i = 0; i < wallNo; i++) {
			double rad, deg;
			fscanf(fptr, "%lf %lf\n", &rad, &deg);
			wallDots[i]->setup(rad / 300.0, -deg);
		}
	}
};