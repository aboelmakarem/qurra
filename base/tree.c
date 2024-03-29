// MeshGen
// Ahmed Hussein (amhussein4@gmail.com)
// March 28th 2024

#include "stdlib.h"
#include "tree.h"
#include "stdio.h"

TreeNode* newNode(TreeNode* parent,int key)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->color = RED;
	return node;
}

void freeNode(TreeNode* node)
{
	if(node == NULL)
	{
		return;
	}
	if(node->left != NULL)
	{
		freeNode(node->left);
	}
	if(node->right != NULL)
	{
		freeNode(node->right);
	}
	free(node);
}

Tree* newTree()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

void freeTree(Tree* tree)
{
	if(tree == NULL)
	{
		return;
	}
	if(tree->root != NULL)
	{
		// free all tree nodes
		freeNode(tree->root);
	}
	free(tree);
}

void rotate(Tree* tree,TreeNode* node,int leftRotate)
{
	// Rotates a tree node, the parent cannot be a null node. 
	TreeNode* parent = node->parent;
	TreeNode* grandParent = parent->parent;
	TreeNode* movedChild = node->right;
	if(leftRotate)
	{
		movedChild = node->left;
	}

	node->parent = grandParent;
	if(grandParent != NULL)
	{
		if(grandParent->left == parent)
		{
			grandParent->left = node;
		}
		else
		{
			grandParent->right = node;
		}
	}
	else
	{
		tree->root = node;
	}

	parent->parent = node;
	if(leftRotate)
	{
		// This is a left rotation, the node is its parent's right child
		node->left = parent;
		// The left child of this node is guaranteed to be greater than the 
		// parent. It becomes the right child of the parent.
		parent->right = movedChild;
	}
	else
	{
		// This is a right rotation, the node is its parent's left child
		node->right = parent;
		// The right child of this node is guaranteed to be less than the 
		// parent. It becomes the left child of the parent.
		parent->left = movedChild;
	}
	if(movedChild != NULL)
	{
		movedChild->parent = parent;
	}
}

void treeBalance(Tree* tree,TreeNode* node)
{
	// Balances a red-black tree according to the red-black tree 
	// rules.
	// 1. The root node is black
	// 2. All null-leaf nodes are black
	// 3. The parent of a red node is a black node
	// 4. The number of black nodes along any path from root to 
	// 		leaves is the same
	// If this is the root node, make it black and return
	while((node->parent != NULL) && (node->parent->color == RED))
	{
		// Parent is red and grandparent is guaranteed to exist
		// Get node's uncle
		TreeNode* parent = node->parent;
		TreeNode* grandParent = parent->parent;
		TreeNode* uncle = NULL;
		if(grandParent->left == parent)
		{
			uncle = grandParent->right;
		}
		else
		{
			uncle = grandParent->left;
		}
		if((uncle == NULL) || (uncle->color == BLACK))
		{
			// Parent and uncle have different colors, we need to 
			// eventually color the parent black and keep the uncle 
			// as it is. If the node is the left[right] child of its parent, 
			// color the parent black, the grandparent red, then right[left]-rotate
			// the parent to become the black grandparent with two red children 
			// (node and grandparent). If the node is the right[left] child of 
			// its parent, left[right]-rotate it and replace it by its parent, 
			// which is now the left child of the node.
			int leftRotate = 0; 
			if(grandParent->left == parent)
			{
				if(parent->right == node)
				{
					rotate(tree,node,1);
					node = parent;
				}
				leftRotate = 0;
			}
			else
			{
				if(parent->left == node)
				{
					rotate(tree,node,0);
					node = parent;
				}
				leftRotate = 1;
			}
			node->parent->color = BLACK;
			grandParent->color = RED;
			rotate(tree,node->parent,leftRotate);
		}
		else
		{
			// both parent and uncle are red, turn them black, turn 
			// the grandparent red, balance the grandparent
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			node = grandParent;
		}
	}
	// If the loop did not execute or it terminated after coloring the root red, 
	// restore it to black. 
	tree->root->color = BLACK;
}

TreeNode* treeInsert(Tree* tree,int key)
{
	TreeNode* parent = NULL;
	TreeNode* node = tree->root;
	while(node != NULL)
	{
		parent = node;
		if(key < node->key)
		{
			// Key is to be inserted left of node, descend the left child path.
			node = node->left;
		}
		else if(key > node->key)
		{
			// Key is to be inserted right of parent, descend the left child path.
			node = node->right;
		}
		else
		{
			// key to be insrted is already in the tree, return 
			// the tree node that holds the key 
			return node;
		}
	}
	// node is null and parent is a parent of a null node. Insert a new node depending on 
	// whether it is a left or a right insertion. 
	node = newNode(parent,key);
	if(parent == NULL)
	{
		// this is the first insertion, the iteration above did not take place
		tree->root = node;
	}
	else if(key < parent->key)
	{
		// left insertion
		parent->left = node;
	}
	else
	{
		// right insertion
		parent->right = node;
	}
	// mark the newly inserted node red
	node->color = RED;
	treeBalance(tree,node);
	return node;
}

void treeRemove(TreeNode* root,int item)
{

}

TreeNode* treeFind(Tree* tree,int key)
{
	TreeNode* node = tree->root;
	while(node != NULL)
	{
		if(key < node->key)
		{
			// Look for key in node's left subtree
			node = node->left;
		}
		else if(key > node->key)
		{
			// Look for key in node's right subtree
			node = node->right;
		}
		else
		{
			// key to be insrted is already in the tree, return 
			// the tree node that holds the key 
			return node;
		}
	}
	return node;
}

TreeNode* previousAncestor(TreeNode* node)
{
	if(node->parent == NULL)
	{
		return NULL;
	}
	if(node->parent->right == node)
	{
		return node->parent;
	}
	return previousAncestor(node->parent);
}

TreeNode* nextAncestor(TreeNode* node)
{
	if(node->parent == NULL)
	{
		return NULL;
	}
	if(node->parent->left == node)
	{
		return node->parent;
	}
	return nextAncestor(node->parent);
}

TreeNode* minDescendent(TreeNode* node)
{
	if(node->left == NULL)
	{
		return node;	
	}
	return minDescendent(node->left);
}

TreeNode* maxDescendent(TreeNode* node)
{
	if(node->right == NULL)
	{
		return node;	
	}
	return maxDescendent(node->right);
}

TreeNode* nodeNext(TreeNode* node)
{
	if(node->right != NULL)
	{
		return minDescendent(node->right);
	}
	return nextAncestor(node);
}
TreeNode* nodePrevious(TreeNode* node)
{
	if(node->left != NULL)
	{
		return maxDescendent(node->left);
	}
	return previousAncestor(node);
}

TreeNode* treeStart(Tree* tree)
{
	if(tree->root == NULL)
	{
		return NULL;
	}
	return minDescendent(tree->root);
}

TreeNode* treeEnd(Tree* tree)
{
	if(tree->root == NULL)
	{
		return NULL;
	}
	return maxDescendent(tree->root);
}

int isSubtreeValid(TreeNode* node)
{
	// Check if any of the following red-black tree rules are violated for the 
	// subtree rooted at this node. 
	// 1. The key of the left child is less than the node's key
	// 2. The key of the right child is greater than the node's key
	// 3. The parent of a red node is a black node
	int redNode = (node->color == RED);
	if(redNode && (node->parent != NULL))
	{
		if(node->parent->color == RED)
		{
			return 3;
		}
	}
	if(node->left != NULL)
	{
		if(redNode)
		{
			if(node->left->color == RED)
			{
				return 3;
			}
		}
		if(node->left->key >= node->key)
		{
			return 1;
		}
		int subtreeValidity = isSubtreeValid(node->left);
		if(subtreeValidity != 0)
		{
			return subtreeValidity;
		}
	}
	if(node->right != NULL)
	{
		if(redNode)
		{
			if(node->right->color == RED)
			{
				return 3;
			}
		}
		if(node->right->key <= node->key)
		{
			return 2;
		}
		int subtreeValidity = isSubtreeValid(node->right);
		if(subtreeValidity != 0)
		{
			return subtreeValidity;
		}
	}
	return 0;
}

unsigned int nodeBlackDepth(TreeNode* node)
{
	unsigned int depth = 0;
	if(node->color == BLACK)
	{
		depth = 1;
	}
	if(node->parent == NULL)
	{
		return depth;
	}
	return (depth + nodeBlackDepth(node->parent));
}

int isTreeValid(Tree* tree)
{
	// Check if any of the rules of red-black trees are violated
	// 1. The key of the left child is less than the node's key
	// 2. The key of the right child is greater than the node's key
	// 3. The parent of a red node is a black node
	// 4. The root node is black
	// 5. All null-leaf nodes are black
	// 6. The number of black nodes along any path from root to 
	// 		leaves is the same
	if(tree->root == NULL)
	{
		return 0;
	}
	if(tree->root->color != BLACK)
	{
		return 4;
	}
	int rootValidity = isSubtreeValid(tree->root);
	if(rootValidity != 0)
	{
		return rootValidity;
	}
	// traverse the tree and comfirm that black depths of all leaves are 
	// equal
	TreeNode* node = treeStart(tree);
	unsigned int depth = 0;
	int firstDepth = 1;
	while(node != NULL)
	{
		if((node->left == NULL) && (node->right == NULL))
		{
			if(firstDepth)
			{
				depth = nodeBlackDepth(node);
				firstDepth = 0;
			}
			else
			{
				if(nodeBlackDepth(node) != depth)
				{
					return 6;
				}
			}
		}
		node = nodeNext(node);
	}
	return 0;
}

void nodePrint(TreeNode* node,unsigned int indentation)
{
	for(unsigned int i = 0 ; i < indentation ; ++i)
	{
		printf("\t");
	}
	if(node->color == RED)
	{
		printf("node [RED] (%d)\n",node->key);
	}
	else
	{
		printf("node [BLACK] (%d)\n",node->key);
	}
	if(node->left != NULL)
	{
		nodePrint(node->left,indentation + 1);
	}
	if(node->right != NULL)
	{
		nodePrint(node->right,indentation + 1);
	}
}

void treePrint(Tree* tree)
{
	if(tree == NULL)
	{
		return;
	}
	if(tree->root == NULL)
	{
		return;
	}
	nodePrint(tree->root,0);
}
