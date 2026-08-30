#include <iostream>
#include <vector>

using namespace std;

void print_array(const vector<int>& array) {
	size_t n=array.size();
	for (size_t i=0; i<n; ++i) {
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

int minimum_number_index(const vector<int>& array) {
	size_t n=array.size();
	if (n==0) {
		return -1;
	}
	int minimum_number=array[0];
	int minimum_index=0;
	for (int i=0; i<n; ++i) {
		if (array[i]<minimum_number) {
			minimum_number=array[i];
			minimum_index=i;
		}
	}
	return minimum_index;
}

int maximum_array_number(const vector<int>& array) {
	size_t n=array.size();
	if (n==0) {
		return -1;
	}
	int maximum_number=array[0];
	for (int i=0; i<n; ++i) {
		if (array[i]>maximum_number) {
			maximum_number=array[i];
		}
	}
	return maximum_number;
}

int maximum_array_number_index(const vector<int>& array) {
	size_t n=array.size();
	if (n==0) {
		return -1;
	}
	int maximum_number=maximum_array_number(array);
	int index=0;
	for (int i=0; i<n; ++i) {
		if (array[i]==maximum_number) {
			index=i;
			break;
		}
	}
	return index;
}

void selection_sort(vector<int>& array) {
	size_t n=array.size();
	for (int i=0; i<n; ++i) {
		if (i==0) {
			/* for first index we need the lowest number and for remaining, we need the smallest greater than the prevoius one. */
			swap(array[i], array[minimum_number_index(array)]);
		} else {
			int previous_element=array[i-1];
			/* taking the maximum number as the correct one for the current position */
			int correct_number=maximum_array_number(array);
			int correct_number_index=maximum_array_number_index(array);
			for (int j=i; j<n; ++j) {
				if (array[j]>=previous_element && array[j]<correct_number) {
					correct_number=array[j];
					correct_number_index=j;
				}
			}
			swap(array[i], array[correct_number_index]);
		}
	}
}

int main() {
	cout<<"Size of array: ";
	size_t n; cin>>n;
	vector<int> array(n, 0);
	cout<<"Elements of the array: ";
	for (int i=0; i<n; ++i) {
		cin>>array[i];
	}
	cout<<"The array: ";
	print_array(array);
	selection_sort(array);
	cout<<"The array after the sorting: ";
	print_array(array);
	return 0;
}
