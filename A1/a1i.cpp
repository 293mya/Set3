#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

struct Position {
  double x;
  double y;
};

struct CircleShape {
  Position center;
  double radius;
};

struct BoundingRectangle {
  Position top_left;
  Position bottom_right;

  double area() {
    return (bottom_right.x - top_left.x) * (top_left.y - bottom_right.y);
  }
};

CircleShape readCircle() {
  CircleShape circle;
  std::cin >> circle.center.x >> circle.center.y >> circle.radius;
  return circle;
}

bool isPointInsideCircle(CircleShape &circle, Position &point) {
  double dx = point.x - circle.center.x;
  double dy = point.y - circle.center.y;
  return (dx * dx + dy * dy) <= (circle.radius * circle.radius);
}

bool isInsideAllCircles(std::vector<CircleShape> &circles, Position &point) {
  for (int i = 0; i < 3; ++i) {
    if (!isPointInsideCircle(circles[i], point)) {
      return false;
    }
  }
  return true;
}

BoundingRectangle
calculateBoundingRectangle(std::vector<CircleShape> &circles) {
  BoundingRectangle region;
  region.top_left.x =
      std::min(circles[0].center.x - circles[0].radius,
               std::min(circles[1].center.x - circles[1].radius,
                        circles[2].center.x - circles[2].radius));
  region.top_left.y =
      std::max(circles[0].center.y + circles[0].radius,
               std::max(circles[1].center.y + circles[1].radius,
                        circles[2].center.y + circles[2].radius));
  region.bottom_right.x =
      std::max(circles[0].center.x + circles[0].radius,
               std::max(circles[1].center.x + circles[1].radius,
                        circles[2].center.x + circles[2].radius));
  region.bottom_right.y =
      std::min(circles[0].center.y - circles[0].radius,
               std::min(circles[1].center.y - circles[1].radius,
                        circles[2].center.y - circles[2].radius));

  return region;
}

double estimateIntersectionArea(BoundingRectangle &region,
                                std::vector<CircleShape> &circles,
                                int sample_count) {
  const int RANDOM_SEED = 42;
  std::mt19937 generator(RANDOM_SEED);
  std::uniform_real_distribution<double> distributionX(region.top_left.x,
                                                       region.bottom_right.x);
  std::uniform_real_distribution<double> distributionY(region.bottom_right.y,
                                                       region.top_left.y);

  int hitCount = 0;
  for (int i = 0; i < sample_count; ++i) {
    Position randomPoint;
    randomPoint.x = distributionX(generator);
    randomPoint.y = distributionY(generator);

    if (isInsideAllCircles(circles, randomPoint)) {
      ++hitCount;
    }
  }

  return region.area() * static_cast<double>(hitCount) /
         static_cast<double>(sample_count);
}

int main() {
  std::vector<CircleShape> circles(3);
  for (int i = 0; i < 3; ++i) {
    circles[i] = readCircle();
  }
  BoundingRectangle region = calculateBoundingRectangle(circles);

  const int SAMPLES = 300000;

  double area = estimateIntersectionArea(region, circles, SAMPLES);

  std::cout << std::fixed << std::setprecision(10) << area << '\n';
  return 0;
}
