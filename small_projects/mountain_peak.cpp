#include <iostream>
#include <vector>
#include "../utilities.hpp"

using namespace std;

int peak_index(const vector<long long>& array, const int& start, const int& end) {
	int mid=(start+end)/2;
	int left=mid-1;
	int right=mid+1;
	if (array[mid]>left && array[mid]<right) {
		/* we are climbing up, so keep moving up */
		return peak_index(array, mid, end);
	} else if (array[mid]<left && array[mid]>array[right]) {
		/* we are climbing down, so go back */
		return peak_index(array, start, mid);
	} else {
		return mid;
	}
}

int main() {
	vector<long long> array=initialize_array();
	cout<<"peak index: "<<peak_index(array, 0, array.size())<<endl;
	return 0;
}
