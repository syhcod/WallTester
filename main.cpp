#include <stdio.h>
#include "Visualizer.h"
#include "Collider.h"


// Wall* root;
// Wall* wall3 = root->back->front;
// Point stPoint = wall3->leftDot;
// a=    m



bool isActual(Vec2 move, Vec2 wall) {
  return false;
}



int main() {

  // 1. 쪼갠 벡터들의 개수
  // 2. 벡터들의 수열
  // Vector vecs[10] = ~;
  // Wall은 root에서 가져옴

  Walls* wallManager = new Walls("./dots", "./walls", 18);
  Vec2* move = new Vec2();
  Vec2* wall = new Vec2();

  Wall* root = wallManager->getRoot();

  move->leftDot->set_x(0);
  move->leftDot->set_y(0);
  move->rightDot->set_x(1);
  move->rightDot->set_y(0);
  wall->leftDot->set_x(0);
  wall->leftDot->set_y(1);
  wall->rightDot->set_x(1.1);
  wall->rightDot->set_y(0);

  Vec2 Vecs[10];
  for (int i = 0; i < 10; i++) {
    Vecs[i] = (i % 2) == 0 ? *move : *wall;
  }

  dot *c=new dot(0.5, 0.5);
  dot *a=new dot(5, 5);

  Collider collider;

  Vec2* yeah = new Vec2();
  yeah->leftDot = c;
  yeah->rightDot = a;

  collider.findWall(yeah, root);
  
  
  Visualizer* visualizer = new Visualizer(root, collider.getVecs(), collider.getVecsNo());
  visualizer->show(true);

  
  delete move;
  delete wall;
  // delete visualizer;
  delete wallManager;
}