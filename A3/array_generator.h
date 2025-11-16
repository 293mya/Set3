#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <cstddef>
#include <vector>

class ArrayGenerator {
public:
  std::vector<int> generateRandomArray(std::size_t size);

  std::vector<int> generateReversedArray(std::size_t size);

  std::vector<int> generateAlmostSortedArray(std::size_t size);
};

#endif
