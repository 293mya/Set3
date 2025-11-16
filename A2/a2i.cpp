#include <iostream>
#include <utility>
#include <vector>

void setupFastIO();
size_t readArraySize();
std::vector<int> readArray(size_t arraySize);
void sort(std::vector<int> &values);
void insertionSortSmall(std::vector<int> &values);
size_t findIndexOfMinimum(const std::vector<int> &values, size_t left,
                          size_t right);
void mergeSort(std::vector<int> &values);
void merge(std::vector<int> &destination, const std::vector<int> &leftPart,
           const std::vector<int> &rightPart);
void printArray(const std::vector<int> &values);

void setupFastIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

size_t readArraySize() {
  size_t size = 0;
  std::cin >> size;
  return size;
}

std::vector<int> readArray(size_t arraySize) {
  std::vector<int> arr(arraySize);
  for (size_t index = 0; index < arraySize; ++index) {
    std::cin >> arr[index];
  }
  return arr;
}

void sort(std::vector<int> &values) {
  const size_t threshold = 15;
  if (values.size() <= threshold) {
    insertionSortSmall(values);
  } else {
    mergeSort(values);
  }
}

void insertionSortSmall(std::vector<int> &values) {
  size_t totalElements = values.size();
  for (size_t currentIndex = 0; currentIndex < totalElements; ++currentIndex) {
    size_t minIndex =
        findIndexOfMinimum(values, currentIndex, totalElements - 1);
    std::swap(values[currentIndex], values[minIndex]);
  }
}

size_t findIndexOfMinimum(const std::vector<int> &values, size_t left,
                          size_t right) {
  size_t indexOfMin = left;
  int minValue = values[left];
  for (size_t i = left + 1; i <= right; ++i) {
    if (values[i] < minValue) {
      minValue = values[i];
      indexOfMin = i;
    }
  }
  return indexOfMin;
}

void mergeSort(std::vector<int> &values) {
  size_t n = values.size();
  size_t middle = n / 2;

  std::vector<int> left(values.begin(), values.begin() + middle);
  std::vector<int> right(values.begin() + middle, values.end());

  sort(left);
  sort(right);

  merge(values, left, right);
}

void merge(std::vector<int> &destination, const std::vector<int> &leftPart,
           const std::vector<int> &rightPart) {
  size_t writeIndex = 0;
  size_t leftIndex = 0;
  size_t rightIndex = 0;

  size_t leftSize = leftPart.size();
  size_t rightSize = rightPart.size();

  while (leftIndex < leftSize && rightIndex < rightSize) {
    if (leftPart[leftIndex] <= rightPart[rightIndex]) {
      destination[writeIndex] = leftPart[leftIndex];
      leftIndex++;
    } else {
      destination[writeIndex] = rightPart[rightIndex];
      rightIndex++;
    }
    writeIndex++;
  }

  while (leftIndex < leftSize) {
    destination[writeIndex++] = leftPart[leftIndex++];
  }

  while (rightIndex < rightSize) {
    destination[writeIndex++] = rightPart[rightIndex++];
  }
}

void printArray(const std::vector<int> &values) {
  for (size_t index = 0; index < values.size(); ++index) {
    std::cout << values[index];
    if (index + 1 != values.size())
      std::cout << ' ';
  }
  std::cout << '\n';
}

int main() {
  setupFastIO();
  size_t len = readArraySize();
  std::vector<int> arr = readArray(len);
  sort(arr);
  printArray(arr);
  return 0;
}
