#include <vector>

#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

class ArrayGenerator {
public:
  std::vector<int> generateRandomArray(size_t);
  std::vector<int> generateReversedArray(size_t);
  std::vector<int> generateAlmostSortedArray(size_t);
};

#endif
