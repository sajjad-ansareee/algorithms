/* last word length */
#include <iostream>
#include <string>

using namespace std;

int last_length(const string& s) {
	/* ignore the white spaces at end */
	int i=s.length()-1;
	while (s[i]==' ' && i>=0) {
		i-=1;
	}
	int length_count=0;
	while (s[i]!=' ' && i>=0) {
		i-=1;
		length_count+=1;
	}
	return length_count;
}

int main() {
	string s; getline(cin, s);
	cout<<last_length(s)<<endl;
	return 0;
}
