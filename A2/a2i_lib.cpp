
#include <algorithm>
#include <cstddef>
#include <vector>

void insertionSortSmall(std::vector<int> &array);
std::size_t findIndexOfMinimumInArrayPart(const std::vector<int> &array,
                                          std::size_t startIndex,
                                          std::size_t endIndex);
void mergeTwoHalves(std::vector<int> &destination,
                    const std::vector<int> &leftHalf,
                    const std::vector<int> &rightHalf);
void mergeSort(std::vector<int> &array);
void sort(std::vector<int> &array);

std::size_t findIndexOfMinimumInArrayPart(const std::vector<int> &array,
                                          std::size_t startIndex,
                                          std::size_t endIndex) {
  std::size_t indexOfMinimum = startIndex;
  int minimumValue = array[startIndex];

  for (std::size_t currentIndex = startIndex + 1; currentIndex <= endIndex;
       ++currentIndex) {
    if (array[currentIndex] < minimumValue) {
      minimumValue = array[currentIndex];
      indexOfMinimum = currentIndex;
    }
  }

  return indexOfMinimum;
}

void insertionSortSmall(std::vector<int> &array) {
  const std::size_t arraySize = array.size();

  for (std::size_t sortedPrefixEnd = 0; sortedPrefixEnd < arraySize;
       ++sortedPrefixEnd) {

    std::size_t indexOfMinimum =
        findIndexOfMinimumInArrayPart(array, sortedPrefixEnd, arraySize - 1);

    if (indexOfMinimum != sortedPrefixEnd) {
      std::swap(array[sortedPrefixEnd], array[indexOfMinimum]);
    }
  }
}

void mergeTwoHalves(std::vector<int> &destination,
                    const std::vector<int> &leftHalf,
                    const std::vector<int> &rightHalf) {
  std::size_t destinationIndex = 0;
  std::size_t leftIndex = 0;
  std::size_t rightIndex = 0;

  while (leftIndex < leftHalf.size() && rightIndex < rightHalf.size()) {
    if (leftHalf[leftIndex] <= rightHalf[rightIndex]) {
      destination[destinationIndex++] = leftHalf[leftIndex++];
    } else {
      destination[destinationIndex++] = rightHalf[rightIndex++];
    }
  }

  while (leftIndex < leftHalf.size()) {
    destination[destinationIndex++] = leftHalf[leftIndex++];
  }

  while (rightIndex < rightHalf.size()) {
    destination[destinationIndex++] = rightHalf[rightIndex++];
  }
}

void mergeSort(std::vector<int> &array) {
  const std::size_t arraySize = array.size();
  if (arraySize <= 1) {
    return;
  }

  const std::size_t middleIndex = arraySize / 2;

  std::vector<int> leftHalf(array.begin(), array.begin() + middleIndex);
  std::vector<int> rightHalf(array.begin() + middleIndex, array.end());

  sort(leftHalf);
  sort(rightHalf);

  mergeTwoHalves(array, leftHalf, rightHalf);
}

void sort(std::vector<int> &array) {
  const std::size_t insertionSortThreshold = 15;

  if (array.size() < insertionSortThreshold) {
    insertionSortSmall(array);
  } else {
    mergeSort(array);
  }
}
