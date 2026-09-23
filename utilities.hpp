#pragma once
#include <vector>


/* array utilities */
std::vector<long long> initialize_array();
void print_array(const std::vector<long long> &array);
long long get_array_sum(const std::vector<long long> &array);
long long get_array_max(const std::vector<long long> &array);
long long get_array_min(const std::vector<long long> &array);
std::vector<long long> get_sorted_array(const std::vector<long long> &array);


/* matrix utilities */
std::vector<std::vector<int>> initialize_matrix();
void print_matrix(const std::vector<std::vector<int>> &matrix);
