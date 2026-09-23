/* find the first index such that the difference between the maximum from start to that and minimum from that to end is at most k */
#include "../utilities.hpp"
#include <iostream>
#include <vector>

using namespace std;

long long get_maxi(const vector<long long>& array, const long long& end) {
    long long maxi=array[0];
    for (long long i=0; i<=end; ++i) {
        maxi=max(maxi, array[i]);
    }
    return maxi;
}

long long get_mini(const vector<long long>& array, const long long& start) {
    long long mini=array[start];
    for (long long i=start; i<array.size(); ++i) {
        mini=min(mini, array[i]);
    }
    return mini;
}

long long firstStableIndex(vector<long long>& nums, long long k) {
    long long index=-1;
    for (long long i=0; i<nums.size(); ++i) {
        if ((get_maxi(nums, i)-get_mini(nums, i))<=k) {
            index=i;
            break;
        }
    }
    return index;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#endif

	vector<long long> array=initialize_array<long long>();
	long long k; cin>>k;
	cout<<"index: "<<firstStableIndex(array, k)<<endl;
    return 0;
}
