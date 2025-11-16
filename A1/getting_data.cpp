#include <cmath>
#include <fstream>
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

  double area() const {
    return (bottom_right.x - top_left.x) * (top_left.y - bottom_right.y);
  }
};

bool isPointInsideCircle(const CircleShape &circle, const Position &point) {
  double dx = point.x - circle.center.x;
  double dy = point.y - circle.center.y;
  return (dx * dx + dy * dy) <= (circle.radius * circle.radius);
}

bool isInsideAllCircles(const std::vector<CircleShape> &circles,
                        const Position &point) {
  for (const auto &circle : circles) {
    if (!isPointInsideCircle(circle, point)) {
      return false;
    }
  }
  return true;
}

BoundingRectangle
calculateBoundingRectangle(const std::vector<CircleShape> &circles) {

  double min_x = circles[0].center.x - circles[0].radius;
  double max_x = circles[0].center.x + circles[0].radius;
  double min_y = circles[0].center.y - circles[0].radius;
  double max_y = circles[0].center.y + circles[0].radius;

  for (int i = 1; i < static_cast<int>(circles.size()); i++) {
    min_x = std::min(min_x, circles[i].center.x - circles[i].radius);
    max_x = std::max(max_x, circles[i].center.x + circles[i].radius);
    min_y = std::min(min_y, circles[i].center.y - circles[i].radius);
    max_y = std::max(max_y, circles[i].center.y + circles[i].radius);
  }

  BoundingRectangle rect;
  rect.top_left = {min_x, max_y};
  rect.bottom_right = {max_x, min_y};
  return rect;
}

double estimateIntersectionArea(const BoundingRectangle &region,
                                const std::vector<CircleShape> &circles,
                                int sample_count) {

  std::mt19937 generator(42);

  std::uniform_real_distribution<double> dist_x(region.top_left.x,
                                                region.bottom_right.x);

  std::uniform_real_distribution<double> dist_y(region.bottom_right.y,
                                                region.top_left.y);

  int hits = 0;

  for (int i = 0; i < sample_count; ++i) {

    Position randomPoint = {dist_x(generator), dist_y(generator)};

    if (isInsideAllCircles(circles, randomPoint)) {
      hits++;
    }
  }

  double fraction = static_cast<double>(hits) / sample_count;

  return region.area() * fraction;
}

std::vector<CircleShape> initializeCircles() {
  std::vector<CircleShape> circles(3);

  circles[0] = {{1.0, 1.0}, 1.0};

  circles[1] = {{1.5, 2.0}, std::sqrt(5.0) / 2.0};
  circles[2] = {{2.0, 1.5}, std::sqrt(5.0) / 2.0};

  return circles;
}
// S = 0.25 * π + 1.25 * arcsin(0.8) - 1
double computeExactArea() { return 0.25 * M_PI + 1.25 * std::asin(0.8) - 1.0; }

double computeRelativeDeviation(double expected, double actual) {
  return std::abs(expected - actual) * 100.0 / expected;
}

int main() {

  std::vector<CircleShape> circles = initializeCircles();

  BoundingRectangle wide = calculateBoundingRectangle(circles);

  std::ofstream square_output("square.csv");
  std::ofstream deviation_output("deviation.csv");

  square_output << "N;square\n";
  deviation_output << "N;deviation\n";

  double exact_area = computeExactArea();

  for (int N = 100; N <= 100000; N += 500) {

    double estimated = estimateIntersectionArea(wide, circles, N);

    double deviation = computeRelativeDeviation(exact_area, estimated);

    square_output << N << ";" << estimated << "\n";

    deviation_output << N << ";" << deviation << "\n";
  }

  square_output.close();
  deviation_output.close();

  return 0;
}
