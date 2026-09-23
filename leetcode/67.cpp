#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

int string_to_int(const string& s) {
	int number=0;
	int power=0;
	for (int i=s.length()-1; i>=0; --i) {
		if (s[i]=='1') {
			number+=pow(2, power);
		}
		power += 1;
	}
	return number;
}

string int_to_string(int n) {
	if (n==0) {
		return "0";
	}
	string result;
	while (n>0) {
		if (n%2==1) {
			result+='1';
		} else {
			result+='0';
		}
		n/=2;
	}
	reverse(result.begin(), result.end());
	return result;
}

string string_sum(const string& a, const string& b) {
	int a_number=string_to_int(a);
	int b_number=string_to_int(b);
	int result_number=a_number+b_number;
	string result=int_to_string(result_number);
	return result;
}

int main() {
	string a; cin>>a;
	string b; cin>>b;
	cout<<string_sum(a, b)<<endl;
	return 0;
}
