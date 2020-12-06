#include <iostream>
#include "TreeNodeT.h"
#include <fstream>

using namespace std;

template <class myType>
class BST {
	public:
		BST() {
			root = NULL; //empty tree
		}

		~BST() {
			destroyRecursive(root);
			//iterate and delete - this is O(n)
		}

		void insertNode(myType value) {
			TreeNode<myType> *node = new TreeNode<myType>(value);

			if (isEmpty())
				root = node;
			else {
				//need to find insertion point
				TreeNode<myType> *current = root;
				TreeNode<myType> *parent = NULL;

				while (true) {
					//iterate to find the correct insertion point
					parent = current;

					if (value->GetId() < current->key->GetId()) {
						//go left
						current = current->left;

						if (current == NULL) {
							//insertion point
							parent->left = node;
							break;
						}
					}

					else {
						//go right
						current = current->right;
						if (current == NULL) {
							parent->right = node;
							break;
						}
					}
				}
			}
		}

		bool searchNode(myType value) {
		 	if (isEmpty())
				return false;
			else {
				//tree is not empty, then search
				TreeNode<myType> *current = root;

				while (current->key != value) {
					if (value < current->key)
						current = current->right;
					else
						current = current->left;

					if (current == NULL)
						return false;
				}
			}
			return true;
		}

		bool searchNodeById(int id) {
		 	if (isEmpty())
				return false;
			else {
				//tree is not empty, then search
				TreeNode<myType> *current = root;

				while (current->key->GetId() != id) {
					if (id < current->key->GetId())
						current = current->right;
					else
						current = current->left; // CHANGED HERE

					if (current == NULL)
						return false;
				}
			}
			return true;
		}
		
		myType getNodeById(int id) {
            //tree is not empty, then search
            TreeNode<myType> *current = root;

            while (current->key->GetId() != id) {
                if (id < current->key->GetId())
                    current = current->right;
                else
                    current = current->left; // CHANGED HERE
            }
            return current->key;
        }

		bool deleteNode(myType k) {
			if (isEmpty()) // root == NULL
				return false;

			//invoke search to determine whether they exist or not

			TreeNode<myType> *parent = NULL;
			TreeNode<myType> *current = root;
			bool isLeftNode = true;

			while (current->key != k) {
				parent = current;

				if (k < current->key) {
					isLeftNode = true;
					current = current->left;
				}
				else {
					isLeftNode = false;
					current = current->right;
				}

				if (current == NULL)
					return false;
			}

			//at this point, we have found our key/value, so proceed to delete this node

			//case: node to be deleted does not have children (a.k.a. Leaf node)

			if  (current->left == NULL && current->right == NULL) {
				if (current == root)
					root = NULL;
				else if (isLeftNode) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
			}

			//case: node to be deleted has one child - determine if descendent is left or right

			else if (current->right == NULL) {
				//does not have a right child, so must have left
		    if (current == root)
		        root = current->left;
		    else {
		        //node to be deleted is a right child
		        parent->right = current->left;
		    }
		        }
		        else if (current->left == NULL) {
		            //does not have left child, so must have right
		    if (current == root)
		        root = current->right;
		    else {
		        //node to be deleted is a right child
		        parent->right = current->right;
		    }
		        }
			else {
				//the node to be deleted has two children - we have to find the successor

				TreeNode<myType> *successor = getSuccessor(current); //current is the node to be deleted

				if (current == root)
					root = successor;
				else if (isLeftNode)
					parent->left = successor;
				else
					parent->right = successor;

				successor->left = current->left;
			}
			//delete (collect garbage) in the function
			return true;
		}

		void destroyRecursive (TreeNode<myType>* node) {
			if (node) {
				destroyRecursive(node->left);
				destroyRecursive(node->right);
				delete node;
		    }
		}

		bool isEmpty() {
		    if (root == NULL)
		        return true;
		    return false;
		}

		myType getMax() {
			if (isEmpty()) {
		        return NULL;
		    }

			TreeNode<myType> *current = root;
			while (current->right != NULL) {
				current = current->right;
			}

			return current->key;
		}

		myType getMin() {
			if (isEmpty()) {
		        return NULL;
		    }

			TreeNode<myType> *current = root;
			while (current->left != NULL) {
				current = current->left;
			}

			return current->key;
		}
		myType getRoot() {
			if (isEmpty()) {
				return NULL;
			}
			return root->key;
		}

		TreeNode<myType>* getSuccessor(TreeNode<myType> *d) {

			TreeNode<myType> *sp = d;
			TreeNode<myType> *successor = d;
			TreeNode<myType> *current = d->right;

			while (current != NULL) {
				sp = successor;
				successor = current;
				current = current->left;
			}

			if (successor != d->right) {
				sp->left = successor->right;
				successor->right = d->right;
			}
			return successor;
		}

		void printTree() {
			recPrint(root);
		}

		// parameter: ofstream& outfile
		void recPrint (TreeNode<myType> *node) {
			if(node != NULL)
			{
				recPrint (node->left);
				node->key->PrintStats();
				recPrint (node->right);
			}
		}
		void printTreeToFile(ofstream& outfile) {
			recPrintToFile(root, outfile);
		}

		// parameter: ofstream& outfile
		void recPrintToFile (TreeNode<myType> *node, ofstream& outfile) {
			if(node != NULL)
			{
				recPrintToFile(node->left, outfile);
				node->key->PrintStatsToFile(outfile);
				recPrintToFile(node->right, outfile);
			}
		}

		void printTreeId() {
			cout << "\nIds:" << endl;
			recPrintTreeId(root);
		}

		void recPrintTreeId(TreeNode<myType> *node) {
			if(node != NULL)
			{
				recPrint (node->left);
				cout << "Hey." << endl;
				cout << node->key->GetId() << endl;
				recPrint (node->right);
			}
		}
		int getSize() {
			return recGetSize(root);
		}
		int recGetSize(TreeNode<myType> *node) {
			if (node == NULL) {
				return 0;
			}

			int left = recGetSize(node->left);
			int right = recGetSize(node->right);

			return 1 + left + right;
		}

		//bool deleter(T k);
		//T nearestAncestor(T a, T b);

	private:
		TreeNode<myType>* root;
		/*
			All BST needs is root, because it only goes left and right from there.
			Parent and child will only be used during runtime.
		*/
};
