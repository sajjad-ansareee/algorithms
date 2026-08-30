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

void bubble_sort(vector<int>& array) {
	size_t n=array.size();
	for (int i=0; i<n; ++i) {
		bool swapped=false;
		for (int j=0; j<n-1-i; ++j) {
			if (array[j]>array[j+1]) {
				swap(array[j], array[j+1]);
				swapped=true;
			}
		}
		if (swapped==false) {
			return;
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
	bubble_sort(array);
	cout<<"The array after the sorting: ";
	print_array(array);
	return 0;
}
