#include <iostream>
#include <random>
#include <vector>

void makeInputFast() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
}

int inputSize() {
  int size = 0;
  std::cin >> size;
  return size;
}

std::vector<int> inputVector(int size) {
  std::vector<int> data(size);
  for (int index = 0; index < size; ++index) {
    std::cin >> data[index];
  }
  return data;
}

void printVector(const std::vector<int> &data) {
  for (int index = 0; index < static_cast<int>(data.size()); ++index) {
    if (index != 0) {
      std::cout << ' ';
    }
    std::cout << data[index];
  }
  std::cout << '\n';
}

int computeMaxRecursionDepth(int size) {
  int depth = 0;
  while (size > 1) {
    size >>= 1;
    ++depth;
  }
  return depth * 2;
}

void insertionSortRange(std::vector<int> &data, int left, int rightExclusive) {
  for (int current = left + 1; current < rightExclusive; ++current) {
    int value = data[current];
    int position = current - 1;
    while (position >= left && data[position] > value) {
      data[position + 1] = data[position];
      --position;
    }
    data[position + 1] = value;
  }
}

void siftDown(std::vector<int> &data, int left, int rightExclusive,
              int rootIndex) {
  int heapSize = rightExclusive - left;

  while (true) {
    int relativeRoot = rootIndex - left;
    int leftChild = left + 2 * relativeRoot + 1;
    if (leftChild >= rightExclusive) {
      break;
    }

    int largestIndex = leftChild;
    int rightChild = leftChild + 1;
    if (rightChild < rightExclusive && data[rightChild] > data[largestIndex]) {
      largestIndex = rightChild;
    }

    if (data[rootIndex] >= data[largestIndex]) {
      break;
    }

    std::swap(data[rootIndex], data[largestIndex]);
    rootIndex = largestIndex;
  }
}

void heapSortRange(std::vector<int> &data, int left, int rightExclusive) {
  int length = rightExclusive - left;
  if (length <= 1) {
    return;
  }

  for (int index = left + (length / 2) - 1; index >= left; --index) {
    siftDown(data, left, rightExclusive, index);
  }

  for (int last = rightExclusive - 1; last > left; --last) {
    std::swap(data[left], data[last]);
    siftDown(data, left, last, left);
  }
}

int randomIndexInRange(int left, int rightInclusive) {
  static std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(left, rightInclusive);
  return distribution(generator);
}

int partitionByRandomPivot(std::vector<int> &data, int left,
                           int rightExclusive) {
  int rightInclusive = rightExclusive - 1;

  int pivotIndex = randomIndexInRange(left, rightInclusive);
  int pivotValue = data[pivotIndex];

  std::swap(data[left], data[pivotIndex]);

  int leftScan = left + 1;
  int rightScan = rightInclusive;

  while (leftScan <= rightScan) {
    if (data[leftScan] <= pivotValue) {
      ++leftScan;
    } else if (data[rightScan] > pivotValue) {
      --rightScan;
    } else {
      std::swap(data[leftScan], data[rightScan]);
      ++leftScan;
      --rightScan;
    }
  }

  int newPivotIndex = leftScan - 1;
  std::swap(data[left], data[newPivotIndex]);
  return newPivotIndex;
}

void introSortRecursive(std::vector<int> &data, int left, int rightExclusive,
                        int remainingDepth) {
  int length = rightExclusive - left;
  if (length <= 1) {
    return;
  }

  const int INSERTION_THRESHOLD = 16;

  if (length < INSERTION_THRESHOLD) {
    insertionSortRange(data, left, rightExclusive);
    return;
  }

  if (remainingDepth == 0) {
    heapSortRange(data, left, rightExclusive);
    return;
  }

  int pivotIndex = partitionByRandomPivot(data, left, rightExclusive);
  int nextDepth = remainingDepth - 1;

  introSortRecursive(data, left, pivotIndex, nextDepth);
  introSortRecursive(data, pivotIndex + 1, rightExclusive, nextDepth);
}

void introSort(std::vector<int> &data) {
  int size = static_cast<int>(data.size());
  if (size <= 1) {
    return;
  }
  int maxDepth = computeMaxRecursionDepth(size);
  introSortRecursive(data, 0, size, maxDepth);
}

int main() {
  makeInputFast();

  int size = inputSize();
  std::vector<int> values = inputVector(size);

  introSort(values);
  printVector(values);

  return 0;
}
