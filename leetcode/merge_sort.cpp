#include "../utilities.hpp"
#include <iostream>
#include <vector>

using namespace std;

// void print_array(const vector<int> &array) {
// 	size_t n = array.size();
// 	for (size_t i = 0; i < n; ++i) {
// 		cout << array[i] << " ";
// 	}
// 	cout << endl;
// }

// vector<int> initialize_array() {
// 	cout << "size of array: ";
// 	size_t n;
// 	cin >> n;
// 	vector<int> array(n, 0);
// 	cout << "elements: ";
// 	for (size_t i = 0; i < array.size(); ++i) {
// 		cin >> array[i];
// 	}
// 	return array;
// }

void get_two_arrays(vector<int>& array, const int& s, const int& m, const int& e, vector<int>& left, vector<int>& right) {
	left.resize(m - s + 1);
	right.resize(e - m);
	for (int i = 0; i < left.size(); ++i) {
		left[i] = array[s + i];
	}
	for (int i = 0; i < right.size(); ++i) {
		right[i] = array[m + 1 + i];
	}
}

void merge(vector<int>& array, const int& s, const int& m, const int& e) {
	vector<int> left, right;
	get_two_arrays(array, s, m, e, left, right);
	int i = 0, j = 0, k = s;
	while (i < left.size() && j < right.size()) {
		if (left[i] <= right[j]) {
			array[k++] = left[i++];
		} else {
			array[k++] = right[j++];
		}
	}
	while (i < left.size()) {
		array[k++] = left[i++];
	}
	while (j < right.size()) {
		array[k++] = right[j++];
	}
}

void merge_sort(vector<int> &array, const int &s, const int &e) {
	/*
	 * s: start
	 * e: end
	 */
	if (s >= e) {
		return;
	} else {
		int m = (s + e) / 2;
		merge_sort(array, s, m);
		merge_sort(array, m + 1, e);
		merge(array, s, m, e);
	}
}

int main() {
	vector<int> array = initialize_array();
	cout << "The array before the sorting: ";
	print_array(array);
	merge_sort(array, 0, array.size() - 1);
	cout << "The array after the sorting: ";
	print_array(array);
	return 0;
}
