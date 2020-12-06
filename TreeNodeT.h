#include <iostream>

using namespace std;
template <class myType>
class TreeNode {
	public:
    myType key; //data as well as the key
    TreeNode *left;
    TreeNode *right;

		TreeNode() {
			left = NULL;
			right = NULL;
		}

		TreeNode(myType k) {
			left = NULL;
			right = NULL;
			key = k;
		}

		~TreeNode() {
			//research and implement
		}
};
