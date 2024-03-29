// MeshGen
// Ahmed Hussein (amhussein4@gmail.com)
// March 28th 2024

#ifndef TREE_H_
#define TREE_H_

enum TreeNodeColor_
{
	RED = 1,
	BLACK = 2
};
typedef enum TreeNodeColor_ TreeNodeColor;

struct TreeNode_
{
	struct TreeNode_* parent;
	struct TreeNode_* left;
	struct TreeNode_* right;
	int key;
	TreeNodeColor color;
};
typedef struct TreeNode_ TreeNode;

struct Tree_
{
	TreeNode* root;
};
typedef struct Tree_ Tree;

TreeNode* newNode(TreeNode* parent,int key);
void freeNode(TreeNode* node);

Tree* newTree();
void freeTree(Tree* tree);

TreeNode* treeInsert(Tree* tree,int key);
void treeRemove(TreeNode* root,int item);
TreeNode* treeFind(Tree* tree,int key);

TreeNode* nodeNext(TreeNode* node);
TreeNode* nodePrevious(TreeNode* node);
TreeNode* treeStart(Tree* tree);
TreeNode* treeEnd(Tree* tree);

int isTreeValid(Tree* tree);
void treePrint(Tree* tree);

#endif

