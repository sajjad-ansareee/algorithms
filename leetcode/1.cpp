/* Two Sum */
#include "../utilities.hpp"
#include <iostream>

using namespace std;

vector<int> two_sum(const vector<long long> &array, const int &target)
{
	vector<int> result(2, 0);
	for (int i = 0; i < array.size(); ++i)
	{
		for (int j = i + 1; j < array.size(); ++j)
		{
			if (array[i] + array[j] == target)
			{
				result[0] = i;
				result[1] = j;
				return result;
			}
		}
	}
	return result;
}

vector<int> optimized_two_sum(const vector<long long> &array, int target)
{
	vector<int> result(2, 0);
	vector<long long> sorted_array = get_sorted_array(array);
	int number_1{};
	int number_2{};
	int left = 0;
	int right = sorted_array.size() - 1;
	while (left < right)
	{
		if (sorted_array[left] + sorted_array[right] == target)
		{
			number_1 = sorted_array[left];
			number_2 = sorted_array[right];
			cout << "Numbers: " << number_1 << " " << number_2 << endl;
			break;
		}
		else if (sorted_array[left] + sorted_array[right] < target)
		{
			++left;
		}
		else
		{
			--right;
		}
	}
	cout << "array: ";
	print_array(array);
	for (int i = 0; i < array.size(); ++i)
	{
		if (array[i] == number_1)
		{
			result[0] = i;
			break;
		}
	}
	for (int i = 0; i < array.size(); ++i)
	{
		if (array[i] == number_2 && i != result[0])
		{
			result[1] = i;
			break;
		}
	}
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#endif

	vector<long long> array = initialize_array();
	cout << "k: ";
	int k;
	cin >> k;
	vector<int> result = optimized_two_sum(array, k);
	cout << "indices: " << result[0] << " " << result[1] << endl;
	return 0;
}
