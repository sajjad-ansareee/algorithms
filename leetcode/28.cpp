/* index of first occurrence of needle in haystack */
#include <iostream>
#include <stack>
#include <string>

using namespace std;

void string_in_stack(const string& s, stack<char>& st) {
	for (int i=s.length()-1; i>=0; --i) {
		st.push(s[i]);
	}
}

void print_stack(stack<char> st) {
	while (st.empty()==false) {
		cout<<st.top()<<" ";
		st.pop();
	}
	cout<<endl;
}

int get_index(const string& haystack, const string& needle) {
	stack<char> h_stack{};
	stack<char> n_stack{};
	string_in_stack(haystack, h_stack);
	int index_count=0;
	while (h_stack.empty()==false) {
		bool found_needle=true;
		for (int j=0; j<needle.length() && h_stack.empty()==false; ++j) {
			if (needle[j]!=h_stack.top()) {
				found_needle=false;
				index_count+=1;
				break;
			}
			h_stack.pop();
			index_count+=1;
		}
		if (found_needle==true) {
			return index_count-needle.length();
		}
		h_stack.pop();
	}
	return -1;
}

int main() {
	string haystack; cin>>haystack;
	string needle; cin>>needle;
	cout<<get_index(haystack, needle)<<endl;
	return 0;
}
