/* same tree */
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool is_same_tree(TreeNode* p, TreeNode* q) {
	/* perform inorder traversal and check if any value mismatch */
	if (p==nullptr && q==nullptr) {
		return true;
	} else if (p==nullptr && q!=nullptr) {
		return false;
	} else if (p!=nullptr && q==nullptr) {
		return false;
	}
	/* check if the left child value, current value, or right child value mismatch */
	return is_same_tree(p->left, q->left) && (p->val==q->val) && is_same_tree(p->right, q->right);
}

int main() {
	return 0;
}
