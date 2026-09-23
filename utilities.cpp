#include "utilities.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

vector<long long> initialize_array() {
	/* input: size of array, elements */
	cout << "size of array: ";
	size_t n;
	cin >> n;
	vector<long long> array(n, 0);
	cout << "elements: ";
	for (size_t i = 0; i < array.size(); ++i) {
		cin >> array[i];
	}
	return array;
}

void print_array(const vector<long long> &array) {
	size_t n = array.size();
	for (size_t i = 0; i < n; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
}

long long get_array_sum(const std::vector<long long> &array) {
	return accumulate(array.begin(), array.end(), 0);
}

long long get_array_max(const vector<long long> &array) {
	if (array.empty()) {
		throw std::invalid_argument("array is empty");
	}
	return *(max_element(array.begin(), array.end()));
}

long long get_array_min(const vector<long long> &array) {
	if (array.empty()) {
		throw std::invalid_argument("array is empty");
	}
	return *(min_element(array.begin(), array.end()));
}

vector<long long> get_sorted_array(const vector<long long> &array) {
	vector<long long> sorted_array = array;
	sort(sorted_array.begin(), sorted_array.end());
	return sorted_array;
}

vector<vector<int>> initialize_matrix() {
	cout<<"rows: ";
	size_t rows; cin>>rows;
	cout<<"columns: ";
	size_t columns; cin>>columns;
	vector<vector<int>> matrix(rows, vector<int>(columns));
	cout<<"elements: "<<endl;
	for (size_t i=0; i<rows; ++i) {
		cout<<"row#"<<i<<": ";
		for (size_t j=0; j<columns; ++j) {
			cin>>matrix[i][j];
		}
	}
	return matrix;
}

void print_matrix(const vector<vector<int>>& matrix) {
	size_t rows=matrix.size();
	if (rows==0) {
		return;
	}
	size_t columns=matrix[0].size();
	for (size_t i=0; i<rows; ++i) {
		for (size_t j=0; j<columns; ++j) {
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}
