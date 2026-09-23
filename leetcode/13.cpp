/* roman to integer */
#include <iostream>
#include <unordered_map>

using namespace std;

int roman_to_int(string s) {
	// unordered_map<char, int> value{};
	// value['I']=1;
	// value['V']=5;
	// value['X']=10;
	// value['L']=50;
	// value['C']=100;
	// value['D']=500;
	// value['M']=1000;
	int result=0;
	for (int i=0; i<s.length(); ++i) {
		if (s[i]=='I') {
			if (i!=s.length()-1 && s[i+1]=='V') {
				result+=4;
				++i;
			} else if (i!=s.length()-1 && s[i+1]=='X') {
				result+=9;
				++i;
			}
			else {
				result+=1;
			}
		} else if (s[i]=='V') {
			result+=5;
		} else if (s[i]=='X') {
			if (i!=s.length()-1 && s[i+1]=='L') {
				result+=40;
				++i;
			} else if (i!=s.length()-1 && s[i+1]=='C') {
				result+=90;
				++i;
			} else {
				result+=10;
			}
		} else if (s[i]=='L') {
			result+=50;
		} else if (s[i]=='C') {
			if (i!=s.length()-1 && s[i+1]=='D') {
				result+=400;
				++i;
			} else if (i!=s.length()-1 && s[i+1]=='M') {
				result+=900;
				++i;
			}
			else {
				result+=100;
			}
		} else if (s[i]=='D') {
			result+=500;
		} else if (s[i]=='M') {
			result+=1000;
		}
		// result+=value[s[i]];
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

	string s; cin>>s;
	cout<<"string: "<<s<<endl;
	cout<<roman_to_int(s)<<endl;
	return 0;
}
