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

vector<vector<int>> transpose_matrix(const vector<vector<int>>& matrix) {
	size_t rows=matrix.size();
	size_t columns=matrix[0].size();
	vector<vector<int>> final(columns, vector<int>(rows, 0));
	if (rows==0) {
		cout<<"matrix is empty..."<<endl;
	} else {
		for (int i=0; i<rows; ++i) {
			for (int j=0; j<columns; ++j) {
				final[j][i]=matrix[i][j];
			}
		}
	}
	return final;
}

int main() {
	vector<vector<int>> a=initialize_matrix();
	cout<<"matrix before transpose: "<<endl;
	print_matrix(a);
	vector<vector<int>> b=transpose_matrix(a);
	cout<<"matrix after transpose: "<<endl;
	print_matrix(b);
	return 0;
}
