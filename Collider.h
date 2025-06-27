#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
struct backdoor {
  bool isColl;
  double s;
};


class Collider {
public:
	backdoor isCollision(Vec2* move, Vec2* wall) {
	  // TODO: Actual collision vs non-acutal collision
	  backdoor ba;
	  double xi=move->leftDot->poll_x();
	  double yi=move->leftDot->poll_y();
	  double xf=move->rightDot->poll_x();
	  double yf=move->rightDot->poll_y();
	  double a=wall->leftDot->poll_x();
	  double b=wall->leftDot->poll_y();
	  double c=wall->rightDot->poll_x();
	  double d=wall->rightDot->poll_y();
	  double det=((d-b)*(xf-xi)-(c-a)*(yf-yi));
	  if (det==0) ba.isColl=false;
	  double t=((yi-b)*(xf-xi)-(xi-a)*(yf-yi))/det;
	  double s=((yi-b)*(c-a)-(xi-a)*(d-b))/det;
	  //printf("%lf\n", s);
	  //printf("%lf\n", t);
	  if (0<=t && t<=1 && 0<=s && s<=1) ba.isColl=true;
	  ba.isColl=false;
	
	  ba.s=s;
	
	  return ba;
	  //bool collision = false;
	  //if (collision) {
		//return isActual(move, wall);
	  //} else {
		//return false;
	  //}
	
	}
	static bool isWoo(dot* c, Wall* well)
	{
	  Vec2* wall = well->vec2();
	  dot* a=wall->leftDot;
	  dot* b=wall->rightDot;

	  dot v1=*c-*a;
	  dot v2=*b-*a;

	  double v3=(v1.poll_x())*(v2.poll_y())-(v1.poll_y())*(v2.poll_x());

	  if (v3>0) return true;
	  else return false;
	}

	void findWall(Vec2* move, Wall* root)
	{
		printf("yeah\n");
		if (root==NULL)
		{
		printf("Got in\n");
		vecs.push_back(*move);
		return;
		}

	  bool a=isWoo(move->leftDot,root);
	  bool b= isWoo(move->rightDot,root);
	  if (a!=b)
	  {
		s=isCollision(move,root->vec2()).s;
		Vec2* vi;
		Vec2* vf;

		dot l = *(move->leftDot);
		dot r = *(move->rightDot);
		vi->leftDot->set_x(l);
		vi->leftDot->set_y(l);
		vi->rightDot->set_x((l)+(r-l)*s);
		vi->rightDot->set_y((l)+(r-l)*s);

		vf->leftDot->set_x((l)+(r-l*s));
		vf->leftDot->set_y((l)+(r-l*s));
		vf->rightDot->set_x(r);
		vf->rightDot->set_y(r);

		findWall(vi,root->front);
		if(isCollision(move,root->vec2()).isColl)
		{
			Vec2* nVec = new Vec2();
			dot vfDir = *(vf->rightDot)-*(vf->leftDot);
			dot wallDir = *(root->rightDot)-*(root->leftDot);
			nVec->leftDot=vf->leftDot;
			nVec->rightDot->set(*(vf->leftDot)+(wallDir)*((vfDir.poll_x())*(wallDir.poll_x()+(vfDir.poll_y())*(wallDir.poll_y()))/(vfDir.poll_x()*vfDir.poll_x()+vfDir.poll_y()*vfDir.poll_y())));
			//nVec 정사영시킨다.

			findWall(nVec,root->front);
		}
		findWall(vf,root->back);
	  }

	  else
	  {
		findWall(move,root->back);
	  }
	}

	Vec2* getVecs() {
		return vecs.data();
	}

	int getVecsNo() {
		return vecs.size();
	}
private:
	std::vector<Vec2> vecs;
	double s;
};
//우흥 북딱
// 예아!