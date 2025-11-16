#include "a3i.h"
#include "array_generator.h"

#include <chrono>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

void introSort(std::vector<int> &array, int start_index, int end_index,
               int remaining_recursion_level);
int getMaxRecursionLevel(int size);
int permutateArrayAndReturnPivotIndex(std::vector<int> &array, int start_index,
                                      int end_index);

void quickSortWrapper(std::vector<int> &array);
void quickSortImpl(std::vector<int> &array, int start_index, int end_index);
void introSortWrapper(std::vector<int> &array);

static void writeHeader(std::ofstream &stream) { stream << "size;time\n"; }

static void writeEntry(std::ofstream &stream, std::size_t size,
                       std::int64_t time_ns) {
  stream << size << ';' << time_ns << '\n';
}

static std::int64_t measureQuickSort(std::vector<int> &array) {
  auto begin = std::chrono::high_resolution_clock::now();
  quickSortWrapper(array);
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
      .count();
}

static std::int64_t measureIntroSort(std::vector<int> &array) {
  auto begin = std::chrono::high_resolution_clock::now();
  introSortWrapper(array);
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
      .count();
}

int main() {
  ArrayGenerator generator;

  const std::size_t max_array_size = 10000;
  std::vector<int> base_random = generator.generateRandomArray(max_array_size);
  std::vector<int> base_reversed =
      generator.generateReversedArray(max_array_size);
  std::vector<int> base_almost =
      generator.generateAlmostSortedArray(max_array_size);

  std::ofstream random_quick_file("random_array_std_sort.csv");
  std::ofstream random_intro_file("random_array_intro_sort.csv");
  std::ofstream reversed_quick_file("reversed_array_std_sort.csv");
  std::ofstream reversed_intro_file("reversed_array_intro_sort.csv");
  std::ofstream almost_quick_file("almost_sorted_array_std_sort.csv");
  std::ofstream almost_intro_file("almost_sorted_array_intro_sort.csv");

  writeHeader(random_quick_file);
  writeHeader(random_intro_file);
  writeHeader(reversed_quick_file);
  writeHeader(reversed_intro_file);
  writeHeader(almost_quick_file);
  writeHeader(almost_intro_file);

  const std::size_t start_size = 500;
  const std::size_t end_size = 10000;
  const std::size_t step = 100;

  for (std::size_t current_size = start_size; current_size <= end_size;
       current_size += step) {
    std::vector<int> random_part_quick(base_random.begin(),
                                       base_random.begin() + current_size);
    std::vector<int> random_part_intro = random_part_quick;

    std::vector<int> reversed_part_quick(base_reversed.begin(),
                                         base_reversed.begin() + current_size);
    std::vector<int> reversed_part_intro = reversed_part_quick;

    std::vector<int> almost_part_quick(base_almost.begin(),
                                       base_almost.begin() + current_size);
    std::vector<int> almost_part_intro = almost_part_quick;

    std::int64_t random_quick_time = measureQuickSort(random_part_quick);
    std::int64_t random_intro_time = measureIntroSort(random_part_intro);

    std::int64_t reversed_quick_time = measureQuickSort(reversed_part_quick);
    std::int64_t reversed_intro_time = measureIntroSort(reversed_part_intro);

    std::int64_t almost_quick_time = measureQuickSort(almost_part_quick);
    std::int64_t almost_intro_time = measureIntroSort(almost_part_intro);

    writeEntry(random_quick_file, current_size, random_quick_time);
    writeEntry(random_intro_file, current_size, random_intro_time);

    writeEntry(reversed_quick_file, current_size, reversed_quick_time);
    writeEntry(reversed_intro_file, current_size, reversed_intro_time);

    writeEntry(almost_quick_file, current_size, almost_quick_time);
    writeEntry(almost_intro_file, current_size, almost_intro_time);
  }

  return 0;
}

void quickSortWrapper(std::vector<int> &array) {
  if (array.empty()) {
    return;
  }
  quickSortImpl(array, 0, static_cast<int>(array.size()) - 1);
}

void quickSortImpl(std::vector<int> &array, int start_index, int end_index) {
  if (start_index >= end_index) {
    return;
  }

  int pivot_index =
      permutateArrayAndReturnPivotIndex(array, start_index, end_index);
  if (start_index < pivot_index) {
    quickSortImpl(array, start_index, pivot_index);
  }
  if (pivot_index + 1 < end_index) {
    quickSortImpl(array, pivot_index + 1, end_index);
  }
}

void introSortWrapper(std::vector<int> &array) {
  if (array.empty()) {
    return;
  }
  int max_level = getMaxRecursionLevel(static_cast<int>(array.size()));
  introSort(array, 0, static_cast<int>(array.size()) - 1, max_level);
}
