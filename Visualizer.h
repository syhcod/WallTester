#include "wallTest.h"

class Visualizer {
private:
	Wall* root;
	int wallNo;
	Vec2* Vecs;
	bool printed1 = false;
	bool printed2 = false;
public:
	Visualizer(Wall* root, Vec2* Vecs, int wallNo) {
		this->root = root;
		this->Vecs = Vecs;
		this->wallNo = wallNo;
	}
	static void showWalls(Wall* root) {
		// printf("Root!\n");
		if (root->front != nullptr) {
			// printf("Going front\n");
			showWalls(root->front);
			// printf("Exiting front\n");
		}
		if (root->back != nullptr) {
			// printf("Going back\n");
			showWalls(root->back);
			// printf("Exiting back\n");
		}
		double vx = root->rightDot->poll_x() - root->leftDot->poll_x();
		double vy = root->rightDot->poll_y() - root->leftDot->poll_y();
		printf("L((%.2lf, %.2lf),(%.2lf, %.2lf))\n", root->leftDot->poll_x(), root->leftDot->poll_y(), vx, vy);
	}

	static void showVecs(Vec2* Vecs, int wallNo) {
		for (int i = 0; i < wallNo; i++) {
			double wx = Vecs[i].rightDot->poll_x() - Vecs[i].leftDot->poll_x();
			double wy = Vecs[i].rightDot->poll_y() - Vecs[i].leftDot->poll_y();
			printf("V((%.2lf, %.2lf),(%.2lf, %.2lf))\n", Vecs[i].leftDot->poll_x(), Vecs[i].leftDot->poll_y(), wx, wy);
		}
	}

	static void intitialize() {
		printf("V\\left(a,p\\right)=\\operatorname{polygon}\\left(a,a+p,a+p+\\frac{1}{2}R_{a}\\left(p\\right),a+p,a+p+\\frac{1}{2}R_{b}\\left(p\\right),a+p,a\\right)\n");
		printf("c_{is}\\left(\\theta\\right)=\\left(\\cos\\theta,\\sin\\theta\\right)\n");
		printf("R_{a}\\left(v\\right)=c_{is}\\left(\\arctan\\left(v.y,v.x\\right)-\\frac{9\\pi}{10}\\right)\n");
		printf("R_{b}\\left(v\\right)=c_{is}\\left(\\arctan\\left(v.y,v.x\\right)+\\frac{9\\pi}{10}\\right)\n");
		printf("L\\left(a,p\\right)=\\operatorname{polygon}\\left(a,p+a,a\\right)\n");
	}
	void show(bool ifInitialize) {
		if (ifInitialize) {
			intitialize();
		}
		showVecs(Vecs, wallNo);
		showWalls(root);
	}
};