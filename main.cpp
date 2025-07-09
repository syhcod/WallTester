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

  Wall* root = wallManager->getRoot();
  

  dot *c=new dot(6, -10);
  dot *a=new dot(20, -10);

  Collider collider;

  Vec2 yeah(*c, *a);

  Vec2* vecs = collider.collider(root, yeah);
  
  
  Visualizer* visualizer = new Visualizer(root, vecs, collider.getLength());
  visualizer->show(true);

  
  // delete visualizer;
  delete wallManager;
}