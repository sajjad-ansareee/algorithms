/* inorder tree traversal */
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : value(x), left(left), right(right) {}
};

void build_array(TreeNode* root, vector<int>& array) {
	if (root==nullptr) {
		return;
	}
	build_array(root->left, array);
	array.push_back(root->value);
	build_array(root->right, array);
}

vector<int> inorder(TreeNode* root) {
	vector<int> array;
	build_array(root, array);
	return array;
}

int main() {
	vector<int> a=inorder(nullptr);
	cout<<a[0];
	return 0;
}
