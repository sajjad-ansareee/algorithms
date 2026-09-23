/* symmetric/mirror tree */
/* preorder: 1, 2, 3, 4, 2, 4, 3 */
/* inorder: 3, 2, 4, 1, 4, 2, 3 */
/* 0, 3, 0, 2, 0, 4, 0, 1, 0, 4, 0, 2, 0, 3, 0 */
/* postorder: 3, 4, 2, 4, 3, 2, 1 */

/* another approach to swap the left child with the right child in the post order traversal */

/* another approach is that each level should be palindrome */

#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void build_array(TreeNode* root, vector<int>& array) {
	if (root==nullptr) {
		return;
	}
	build_array(root->left, array);
	array.push_back(root->val);
	build_array(root->right, array);
}

bool is_symmetric(TreeNode* root) {
	vector<int> inorder_array;
	build_array(root, inorder_array);
	if (inorder_array.size()==0) {
		return true;
	} else if (inorder_array.size()%2==0) {
		return false;
	}
	int i=0, j=inorder_array.size()-1;
	while(i<j) {
		if (inorder_array[i]!=inorder_array[j]) {
			return false;
		}
		i+=1;
		j-=1;
	}
	return true;
}











/* check palindrome on each level */



int main() {
	return 0;
}
