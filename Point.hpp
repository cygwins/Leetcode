#ifndef POINT_H_
#define POINT_H_
#include <algorithm>
#include <string>
#include <queue>
#include <cctype>
#include <locale>
#include <memory>
#include <cmath>
using std::vector;

namespace Geometry
{

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

bool operator==(const Point &A, const Point &B) {
    return A.x == B.x && A.y == B.y;
}

bool operator!=(const Point &A, const Point &B) {
    return !(A == B);
}

bool operator<(const Point &A, const Point &B) {
    return A.x < B.x || (A.x == B.x && A.y < B.y);
}

Point operator+(const Point &A, const Point &B) {
    return Point(A.x + B.x, A.y + B.y);
}

Point operator-(const Point &A, const Point &B) {
    return Point(A.x - B.x, A.y - B.y);
}

int operator*(const Point &A, const Point &B) { // point-wise product
    return A.x * B.x + A.y * B.y;
}

int Xprod(const Point &A, const Point &B) { // > 0 if A -> B is anti-clockwise
    return A.x * B.y - B.x * A.y;
}

double len(const Point &A) {
    return sqrt(A.x * A.x + A.y * A.y);
}

double angle(const Point &A, const Point &B) { // A . B == |A||B|cos(alpha)
    return acos( (A * B) / (len(A) * len(B)) );
}

Point parsePoint(const vector<int> &p) {
    return Point(p[0], p[1]);
}

vector<Point> parsePoints(const vector<vector<int>> &ps) {
    vector<Point> points;
    for(int i = 0; i < ps.size(); ++i) {
        points.push_back( parsePoint( ps[i] ));
    }
    return points;
}

vector<int> printPoint(const Point &P) {
    return vector<int>{ P.x, P.y };
}

vector<vector<int>> printPoints(const vector<Point> &Ps) {
    vector<vector<int>> points;
    for(int i = 0; i < Ps.size(); ++i) {
        points.push_back( printPoint( Ps[i] ));
    }
    return points;
}

}
#endif
