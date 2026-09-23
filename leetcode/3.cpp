/* Longest Substring Without Repeating Characters */
#include <bits/stdc++.h>

using namespace std;

int longest_sequence(const string& s) {
	int max_count{};
	int current_count{};
	for (int i=0; i<s.length(); ++i) {
		vector<bool> has_character(256, false);
		for (int j=i; j<s.length(); ++j) {
			unsigned char c=s[j];
			if (has_character[c]==true) {
				break;
			} else {
				has_character[c]=true;
				current_count+=1;
			}
		}
		max_count=max(max_count, current_count);
		current_count=0;
	}
	return max_count;
}

int main() {
	cout<<"string: ";
	string s; cin>>s;
	cout<<longest_sequence(s)<<endl;
}
