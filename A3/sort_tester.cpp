#include "sort_tester.h"

void SortTester::printHeadersIntoStream(std::ofstream &output) {
    output << "array_size;time\n";
}

void SortTester::saveSortingParametersIntoStream(std::ofstream &output, size_t array_size, int64_t sorting_time) {
    output << array_size << ';' << sorting_time << '\n';
}
