#include <iostream>
#include <vector>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

bool onSegment(Point p, Point q, Point r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2;  // Clockwise or counterclockwise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::vector<Point> points;
        for (int j = 0; j < 4; ++j) {
            int x, y;
            char comma;
            std::cin >> x >> comma >> y;
            points.emplace_back(x, y);
        }

        bool intersects = doIntersect(points[0], points[1], points[2], points[3]);
        std::cout << (intersects ? "True" : "False") << std::endl;
    }

    return 0;
}
