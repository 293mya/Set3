#include "array_generator.h"

#include <algorithm>
#include <random>
#include <vector>

std::vector<int> ArrayGenerator::generateRandomArray(std::size_t size) {
  const int minimum_value = 0;
  const int maximum_value = 6000;

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> distribution(minimum_value, maximum_value);

  std::vector<int> array(size);
  for (std::size_t i = 0; i != size; ++i) {
    array[i] = distribution(mt);
  }

  return array;
}

std::vector<int> ArrayGenerator::generateReversedArray(std::size_t size) {
  std::vector<int> array(size);
  for (std::size_t i = 0; i != size; ++i) {
    array[i] = static_cast<int>(size - i);
  }
  return array;
}

std::vector<int> ArrayGenerator::generateAlmostSortedArray(std::size_t size) {
  std::vector<int> array(size);
  for (std::size_t i = 0; i != size; ++i) {
    array[i] = static_cast<int>(i);
  }

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> distribution(0, static_cast<int>(size - 1));

  const std::size_t swaps_amount = size / 100;
  for (std::size_t i = 0; i != swaps_amount; ++i) {
    int first_index = distribution(mt);
    int second_index = distribution(mt);
    std::swap(array[first_index], array[second_index]);
  }

  return array;
}
