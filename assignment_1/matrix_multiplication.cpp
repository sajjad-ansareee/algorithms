#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> initialize_matrix() {
	cout<<"rows: ";
	size_t rows; cin>>rows;
	cout<<"columns: ";
	size_t columns; cin>>columns;
	vector<vector<int>> matrix(rows, vector<int>(columns));
	cout<<"elements: "<<endl;
	for (size_t i=0; i<rows; ++i) {
		cout<<"row#"<<i<<": ";
		for (size_t j=0; j<columns; ++j) {
			cin>>matrix[i][j];
		}
	}
	return matrix;
}

void print_matrix(const vector<vector<int>>& matrix) {
	size_t rows=matrix.size();
	if (rows==0) {
		return;
	}
	size_t columns=matrix[0].size();
	for (size_t i=0; i<rows; ++i) {
		for (size_t j=0; j<columns; ++j) {
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

vector<vector<int>> matrix_multiplication(const vector<vector<int>>& a, const vector<vector<int>>& b) {
	size_t a_rows=a.size();
	size_t a_columns=a[0].size();
	size_t b_rows=b.size();
	size_t b_columns=b[0].size();
	vector<vector<int>> final(a_rows, vector<int>(b_columns, 0));
	if (a_columns!=b_rows) {
		cout<<"multiplication not possible..."<<endl;
	} else {
		int sum=0;
		for (int i=0; i<a_rows; ++i) {
			for (int j=0; j<b_columns; ++j) {
				for (int k=0; k<a_columns; ++k) {
					final[i][j] += (a[i][k]*b[k][j]);
				}
			}
		}
	}
	return final;
}

int main() {
	vector<vector<int>> a=initialize_matrix();
	vector<vector<int>> b=initialize_matrix();
	print_matrix(a);
	print_matrix(b);
	cout<<"the final matrix: "<<endl;
	print_matrix(matrix_multiplication(a, b));
	return 0;
}
