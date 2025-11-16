#include <chrono>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#ifndef SORT_TESTER_H
#define SORT_TESTER_H

class SortTester {
public:
    template<class SortingFunction>
    void storeTimeMeasurmentsOfSortingVectors(std::vector<int> &array, std::string path_to_store_data, SortingFunction sorter) {
        std::ofstream output(path_to_store_data);
        printHeadersIntoStream(output);
        const int start_size = 500;
        const int max_array_size = 10000;
        const int step = 500;
        for (int size = start_size; size <= max_array_size; size += step) {
            std::vector<int> array_part(array.begin(), array.begin() + size);
            int64_t time = sortVectorAndGetTimeOfSorting(array_part, sorter);
            saveSortingParametersIntoStream(output, size, time);
        }
        output.close();
    }

    void printHeadersIntoStream(std::ofstream &output);
    template<class SortingFunction>
    int64_t sortVectorAndGetTimeOfSorting(std::vector<int> &array, SortingFunction sorter) {
        auto start = std::chrono::high_resolution_clock::now();
        sorter(array);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        int64_t nanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
        return nanosec;
    }
    void saveSortingParametersIntoStream(std::ofstream &output, size_t array_size, int64_t sorting_time);
};

#endif
