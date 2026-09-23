/* the subarray with the maximum sum */
#include "../utilities.hpp"
#include <iostream>
#include <vector>

using namespace std;

long long max_subarray_sum(const vector<long long>& array) {
	if (array.empty()) {
		return 0;
	}

	long long current_sum=array[0];
	long long maximum_sum=array[0];
	for (size_t i=1; i<array.size(); ++i) {
		current_sum=max(array[i], current_sum+array[i]);
		maximum_sum=max(maximum_sum, current_sum);
	}
	return maximum_sum;
}

/* 3, -4, 2, 4, -2, 5 */

int main() {
	vector<long long> array=initialize_array();
	cout<<"maximum subarray sum: "<<max_subarray_sum(array)<<endl;
	return 0;
}
