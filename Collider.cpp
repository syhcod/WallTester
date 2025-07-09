#include "Collider.h"

void printwall(Wall* root) {
    dot df = *(root->rightDot) - *(root->leftDot);
    printf("L((%.2lf, %.2lf),(%.2lf, %.2lf))\n", root->leftDot->poll_x(), root->leftDot->poll_y(), df.poll_x(), df.poll_y());
}

void printVec(Vec2 move) {
    dot f = move.getFinish();
    dot s = move.getStart();
    dot df = f - s;
    float wx = df.poll_x();
    float wy = df.poll_y();
    printf("V((%.2lf, %.2lf),(%.2lf, %.2lf))\n", s.poll_x(), s.poll_y(), wx, wy);
}

Vec2* Collider::collider(Wall* root, Vec2 move) {
    this->root = root;
    cutVec.setVec(move.getStart(), move.getFinish());
    Wall* p = findWall(root, move);
    
    if (cutVec.getStart().poll_x() != move.getStart().poll_x()) {
        printf("칸막이\n");
        Vec2 nVec = normalVec(cWall, cutVec.getStart(), cutVec.getFinish());
        dot st = nVec.getStart();
        dot ed = nVec.getFinish();
        dot df = st - ed;
        // printf("V((%.2lf, %.2lf),(%.2lf, %.2lf))\n", st.poll_x(), st.poll_y(), df.poll_x(), df.poll_y());
        return collider(root, normalVec(cWall, cutVec.getStart(), cutVec.getFinish()));
    }
    unsigned int len = vecs.size();
    Vec2* list = (Vec2*)malloc(sizeof(Vec2) * len);
    copy(vecs.begin(), vecs.end(), list);
    return list;
}

unsigned int Collider::getLength() {
    return vecs.size();
}

dot Collider::projection(dot a, dot b, float size2) {
		float times = (a.poll_y() * b.poll_y() + a.poll_x() * b.poll_x()) / size2;
		dot in(a.poll_x() * times, a.poll_y() * times);
		return in;
	}

Vec2 Collider::normalVec(Wall* root, dot start, dot end) {
    Vec2 nVec;
    dot wDiff = *(root->rightDot) - *(root->leftDot);
    dot vDiff = end - start;
    float wsize2 = wDiff.poll_x() * wDiff.poll_x() + wDiff.poll_y() * wDiff.poll_y();
    dot proj = projection(wDiff, vDiff, wsize2);

    nVec.setVec(start, start + proj);
    return nVec;
}

Wall* Collider::findWall(Wall* root, Vec2 move) {
    // printf("L((%.2lf, %.2lf),(%.2lf, %.2lf))\n", root->leftDot->poll_x(), root->leftDot->poll_y(), root->rightDot->poll_x() - root->leftDot->poll_x(), root->rightDot->poll_y() - root->leftDot->poll_y());
    if (root == nullptr) {
        // printf("Null\n");
        vecs.push_back(move);
        return nullptr;
    }

    printwall(root);
    printVec(move);

    if (root == cWall) return findWall(isRightWall ? root->back : root->front, move);

    bool startP = isRight(move.getStart(), root);
    bool endP = isRight(move.getFinish(), root);

    if (startP == endP) return findWall(startP ? root->back : root->front, move);
    else {
        printf("PollColl\n");
    }
    dot* intersect = nullptr;
    SDL_FPoint* inter = new SDL_FPoint;
    bool isTrue = trueCollision(root, move, inter);
    Vec2* L =  nullptr;
    Vec2* R = nullptr;

    intersect = new dot(*inter);
    L = new Vec2(move.getStart(), *intersect);
    R = new Vec2(*intersect, move.getFinish());
    Wall* Left = findWall(root->front, *L);
    if (Left != nullptr) return Left;

    if (isTrue) {
        printf("Collision!\n");
        cutVec.setVec(*intersect, cutVec.getFinish());
        cWall = root;
        isRightWall = startP;
        return root;
    }
    return findWall(root->back, *R);

    if (intersect != nullptr) delete intersect;
    
    return nullptr;
}

bool Collider::isRight(dot c, Wall* wall){
    dot wall_L = *(wall->leftDot);
    dot wall_R = *(wall->rightDot);

    dot v1 = c - wall_L;
    dot v2 = wall_R - wall_L;

    float v3 = (v1.poll_x() * v2.poll_y()) - (v1.poll_y() * v2.poll_x());
    return v3 > 0;
}

bool Collider::trueCollision(Wall* wall, Vec2 move, SDL_FPoint* intersect) {
    // intersect = nullptr;
    
    float yi=move.getStart().poll_y();
    float xi=move.getStart().poll_x();
    float xf=move.getFinish().poll_x();
    float yf=move.getFinish().poll_y();
    float a=wall->leftDot->poll_x();
    float b=wall->leftDot->poll_y();
    float c=wall->rightDot->poll_x();
    float d=wall->rightDot->poll_y();
    float det=((d-b)*(xf-xi)-(c-a)*(yf-yi));
    if (det == 0.0f) {
        return false;
    }
    float t=((yi-b)*(xf-xi)-(xi-a)*(yf-yi))/det;
    float s=((yi-b)*(c-a)-(xi-a)*(d-b))/det;

    if (0<=s && s<=1) {
        // printf("(%f, %f)\n", s, t);
        // printf("Wall: (%f, %f), (%f, %f)\n", a, b, c, d);
        // printf("Move: (%f, %f), (%f, %f)\n", xi, yi, xf, yf);
        float x = xi + (xf - xi) * s;
        float y = yi + (yf - yi) * s;
        intersect->x = x;
        intersect->y = y;

        if (0<=t && t<=1) {
            return true;
        }
    }
    return false;
}