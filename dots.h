#pragma once

static const double dot_rad[9][9] = {
    {5.656854, 5.000000, 4.472136, 4.123106, 4.000000, 4.123106, 4.472136, 5.000000, 5.656854},
    {5.000000, 4.242641, 3.605551, 3.162278, 3.000000, 3.162278, 3.605551, 4.242641, 5.000000},
    {4.472136, 3.605551, 2.828427, 2.236068, 2.000000, 2.236068, 2.828427, 3.605551, 4.472136},
    {4.123106, 3.162278, 2.236068, 1.414214, 1.000000, 1.414214, 2.236068, 3.162278, 4.123106},
    {4.000000, 3.000000, 2.000000, 1.000000, 0.000000, 1.000000, 2.000000, 3.000000, 4.000000},
    {4.123106, 3.162278, 2.236068, 1.414214, 1.000000, 1.414214, 2.236068, 3.162278, 4.123106},
    {4.472136, 3.605551, 2.828427, 2.236068, 2.000000, 2.236068, 2.828427, 3.605551, 4.472136},
    {5.000000, 4.242641, 3.605551, 3.162278, 3.000000, 3.162278, 3.605551, 4.242641, 5.000000},
    {5.656854, 5.000000, 4.472136, 4.123106, 4.000000, 4.123106, 4.472136, 5.000000, 5.656854},
};

static const double dot_deg[9][9] = {
    {2.356194, 2.214297, 2.034444, 1.815775, 1.570796, 1.325818, 1.107149, 0.927295, 0.785398},
    {2.498092, 2.356194, 2.158799, 1.892547, 1.570796, 1.249046, 0.982794, 0.785398, 0.643501},
    {2.677945, 2.553590, 2.356194, 2.034444, 1.570796, 1.107149, 0.785398, 0.588003, 0.463648},
    {2.896614, 2.819842, 2.677945, 2.356194, 1.570796, 0.785398, 0.463648, 0.321751, 0.244979},
    {3.141593, 3.141593, 3.141593, 3.141593, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000},
    {-2.896614, -2.819842, -2.677945, -2.356194, -1.570796, -0.785398, -0.463648, -0.321751, -0.244979},
    {-2.677945, -2.553590, -2.356194, -2.034444, -1.570796, -1.107149, -0.785398, -0.588003, -0.463648},
    {-2.498092, -2.356194, -2.158799, -1.892547, -1.570796, -1.249046, -0.982794, -0.785398, -0.643501},
    {-2.356194, -2.214297, -2.034444, -1.815775, -1.570796, -1.325818, -1.107149, -0.927295, -0.785398},
};

struct SDL_FPoint {
    double x;
    double y;
};

class dot {
public:
    dot() {
        d.x = 0.0f;
        d.y = 0.0f;
    }
    dot(float x, float y) {
        d.x = x;
        d.y = y;
    }

    dot (SDL_FPoint fp) {
        d = fp;
    }
    void setup(double radius, double degree) {
        rad = radius;
        deg = degree;
    }
    
    float poll_x() const {
        return d.x;
    }
    
    float poll_y() const {
        return d.y;
    }

    void cal() {
        d.x = (float)(rad * cos(deg));
        d.y = (float)(rad * sin(deg));
    }

    SDL_FPoint poll_dot() const {
        return d;
    }

    dot operator+(const dot& other) const {
        return dot(poll_x() + other.poll_x(), poll_y() + other.poll_y());
    }

    dot operator-(const dot& other) const {
        return dot(poll_x() - other.poll_x(), poll_y() - other.poll_y());
    }

    dot operator*(const float& other) const {
        return dot(poll_x() * other, poll_y() * other);
    }
private:
    SDL_FPoint d;
    double rad;
    double deg;
};

struct Vec2 {
public:
	Vec2() {
		dot a;
		start = a;
		finish = a;
	}
	Vec2(dot st, dot fin) {
		start = st;
		finish = fin;
	}
	Vec2(float start_x, float start_y, float fin_x, float fin_y) {
		start = dot(start_x, start_y);
		finish = dot(fin_x, fin_y);
	}

	void setVec(dot st, dot fin) {
		start = st;
		finish = fin;
	}

	dot getStart() const {
		return start;
	}
	dot getFinish() const {
		return finish;
	}
private:
	dot start, finish;
};