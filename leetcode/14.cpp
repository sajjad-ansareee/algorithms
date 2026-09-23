/* longest common prefix */
#include <iostream>
#include <vector>

using namespace std;

string longest_prefix(const vector<string>& words) {
	string smallest_word=words[0];
	for (int i=0; i<words.size(); ++i) {
		if (words[i].size()<smallest_word.size()) {
			smallest_word=words[i];
		}
	}
	string result;
	for (int i=0; i<smallest_word.size(); ++i) {
		for (int j=0; j<words.size(); ++j) {
			if (smallest_word[i]!=words[j][i]) {
				return result;
			}
		}
		result+=smallest_word[i];
	}
	return result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n; cin>>n;
	vector<string> words(n);
	for (int i=0; i<n; ++i) {
		cin>>words[i];
	}
	cout<<longest_prefix(words)<<endl;
	return 0;
}
