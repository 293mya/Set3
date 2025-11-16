#ifndef A3I_H
#define A3I_H

#include <vector>

void makeInputFast();
int inputSize();
std::vector<int> inputVector(int size);

int getMaxRecursionLevel(int size);
void introSort(std::vector<int> &array, int start_index, int end_index,
               int remaining_recursion_level);

int permutateArrayAndReturnPivotIndex(std::vector<int> &array, int start_index,
                                      int end_index);

void printVector(const std::vector<int> &array);

#endif
