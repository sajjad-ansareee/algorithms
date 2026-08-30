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

void insertion_sort(vector<int>& array) {
	size_t n=array.size();
	for (size_t i=1; i<n; ++i) {
		int current_element=array[i];
		int correct_position=0;
		/* find the correct position for the current element to be inserted in the already sorted array */
		int j=0;
		while (current_element>=array[j] && j<i) {
			/* j<i will make sure we remain in the sorted array */
			++j;
		}
		correct_position=j;
		/* now shift the remaining elements to the right */
		for (int j=i; j>correct_position; --j) {
			array[j]=array[j-1];
		}
		array[correct_position]=current_element;
	}
}
/* test case failing: 4 2 5 2 8 9 10 2 -1 0 */

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
	insertion_sort(array);
	cout<<"The array after the sorting: ";
	print_array(array);
	return 0;
}
