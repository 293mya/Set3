#include "array_generator.h"

#include <random>
#include <vector>

std::vector<int> ArrayGenerator::generateRandomArray(std::size_t size) {
  const int min_value = 0;
  const int max_value = 6000;

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> dist(min_value, max_value);

  std::vector<int> data(size);
  for (std::size_t index = 0; index < size; ++index) {
    data[index] = dist(rng);
  }
  return data;
}

std::vector<int> ArrayGenerator::generateReversedArray(std::size_t size) {
  std::vector<int> data(size);
  for (std::size_t index = 0; index < size; ++index) {
    data[index] = static_cast<int>(size - index);
  }
  return data;
}

std::vector<int> ArrayGenerator::generateAlmostSortedArray(std::size_t size) {
  std::vector<int> data(size);
  for (std::size_t index = 0; index < size; ++index) {
    data[index] = static_cast<int>(index);
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<std::size_t> dist(0, size - 1);

  const std::size_t swaps_count = size / 100;
  for (std::size_t i = 0; i < swaps_count; ++i) {
    std::size_t first_index = dist(rng);
    std::size_t second_index = dist(rng);
    std::swap(data[first_index], data[second_index]);
  }

  return data;
}
