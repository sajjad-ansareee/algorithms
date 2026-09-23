/* climbing stairs */
#include <iostream>
#include <vector>

using namespace std;

int ways(const int& n) {
	if (n==0) {
		return 0;
	}
	vector<int> array(n, 0);
	array[0]=1;	/* ways for first stair */
	array[1]=2;	/* ways for second stair */
	for (int i=2; i<n; ++i) {
		array[i]=array[i-1]+array[i-2];
	}
	return array[n-1];
}

int main() {
	int n; cin>>n;
	cout<<ways(n)<<endl;
	return 0;
}
